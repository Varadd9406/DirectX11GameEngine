#include "Mesh.h"
#include "imgui/imgui.h"
#include <unordered_map>
#include <sstream>
#include <iostream>
#include "Utility.h"
#include "DynamicConstant.h"
#include "ConstantBuffersEx.h"
#include "LayoutCodex.h"

namespace dx = DirectX;


// Mesh
Mesh::Mesh(Graphics& gfx, std::vector<std::shared_ptr<Bindable>> bindPtrs)
{

	AddBind(std::make_shared<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	for (auto& pb : bindPtrs)
	{
		AddBind(std::move(pb));
	}

	AddBind(std::make_shared<TransformCbuf2>(gfx, *this,0u,2u));
}
void Mesh::Draw(Graphics& gfx, DirectX::FXMMATRIX accumulatedTransform) const 
{
	DirectX::XMStoreFloat4x4(&transform, accumulatedTransform);
	Drawable::Draw(gfx);
}
DirectX::XMMATRIX Mesh::GetTransformXM() const
{
	return DirectX::XMLoadFloat4x4(&transform);
}


// Node
Node::Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform_in)
	:
	id(id),
	meshPtrs(std::move(meshPtrs)),
	name(name)
{
	dx::XMStoreFloat4x4(&transform, transform_in);
	dx::XMStoreFloat4x4(&appliedTransform, dx::XMMatrixIdentity());
}

void Node::Draw(Graphics& gfx, DirectX::FXMMATRIX accumulatedTransform) const
{
	const auto built =
		dx::XMLoadFloat4x4(&appliedTransform) *
		dx::XMLoadFloat4x4(&transform) *
		accumulatedTransform;
	for (const auto pm : meshPtrs)
	{
		pm->Draw(gfx, built);
	}
	for (const auto& pc : childPtrs)
	{
		pc->Draw(gfx, built);
	}
}

void Node::AddChild(std::unique_ptr<Node> pChild)
{
	assert(pChild);
	childPtrs.push_back(std::move(pChild));
}

void Node::ShowTree(Node*& pSelectedNode) const
{
	// if there is no selected node, set selectedId to an impossible value
	const int selectedId = (pSelectedNode == nullptr) ? -1 : pSelectedNode->GetId();
	// build up flags for current node
	const auto node_flags = ImGuiTreeNodeFlags_OpenOnArrow
		| ((GetId() == selectedId) ? ImGuiTreeNodeFlags_Selected : 0)
		| ((childPtrs.size() == 0) ? ImGuiTreeNodeFlags_Leaf : 0);
	// render this node
	const auto expanded = ImGui::TreeNodeEx(
		(void*)(intptr_t)GetId(), node_flags, name.c_str()
	);
	// processing for selecting node
	if (ImGui::IsItemClicked())
	{
		pSelectedNode = const_cast<Node*>(this);
	}
	// recursive rendering of open node's children
	if (expanded)
	{
		for (const auto& pChild : childPtrs)
		{
			pChild->ShowTree(pSelectedNode);
		}
		ImGui::TreePop();
	}
}

void Node::SetAppliedTransform(DirectX::FXMMATRIX transform)
{
	dx::XMStoreFloat4x4(&appliedTransform, transform);
}
const DirectX::XMFLOAT4X4& Node::GetAppliedTransform() const
{
	return appliedTransform;
}

int Node::GetId() const
{
	return id;
}


// Model
class ModelWindow // pImpl idiom, only defined in this .cpp
{
public:
	void Show(const char* windowName, const Node& root)
	{
		// window name defaults to "Model"
		windowName = windowName ? windowName : "Model";
		// need an ints to track node indices and selected node
		int nodeIndexTracker = 0;
		if (ImGui::Begin(windowName))
		{
			ImGui::Columns(2, nullptr, true);
			root.ShowTree(pSelectedNode);

			ImGui::NextColumn();
			if (pSelectedNode != nullptr)
			{
				const auto id = pSelectedNode->GetId();
				auto i = transforms.find(id);
				if (i == transforms.end())
				{
					const auto& applied = pSelectedNode->GetAppliedTransform();
					const auto angles = ExtractEulerAngles(applied);
					const auto translation = ExtractTranslation(applied);
					TransformParameters tp;
					tp.roll = angles.x;
					tp.pitch = angles.y;
					tp.yaw = angles.z;
					tp.x = translation.x;
					tp.y = translation.y;
					tp.z = translation.z;
					std::tie(i, std::ignore) = transforms.insert({ id,tp });
				}
				auto& transform = i->second;
				ImGui::Text("Orientation");
				ImGui::SliderAngle("Roll", &transform.roll, -180.0f, 180.0f);
				ImGui::SliderAngle("Pitch", &transform.pitch, -180.0f, 180.0f);
				ImGui::SliderAngle("Yaw", &transform.yaw, -180.0f, 180.0f);
				ImGui::Text("Position");
				ImGui::SliderFloat("X", &transform.x, -20.0f, 20.0f);
				ImGui::SliderFloat("Y", &transform.y, -20.0f, 20.0f);
				ImGui::SliderFloat("Z", &transform.z, -20.0f, 20.0f);
			}
		}
		ImGui::End();
	}
	dx::XMMATRIX GetTransform() const
	{
		assert(pSelectedNode != nullptr);
		const auto& transform = transforms.at(pSelectedNode->GetId());
		return TransformationMatrix(transform.roll,transform.pitch, transform.yaw, transform.x, transform.y, transform.z);
	}
	Node* GetSelectedNode() const
	{
		return pSelectedNode;
	}
private:
	Node* pSelectedNode;
	struct TransformParameters
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};
	std::unordered_map<int, TransformParameters> transforms;
};

Model::Model(Graphics& gfx, MODEL_DESC desc)
	:
	pWindow(std::make_unique<ModelWindow>())
{
	Assimp::Importer imp;
	const auto pScene = imp.ReadFile(desc.model_path.c_str(),
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_ConvertToLeftHanded |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace
	);

	for (size_t i = 0; i < pScene->mNumMeshes; i++)
	{
		meshPtrs.push_back(ParseMesh(gfx, *pScene->mMeshes[i],desc));
	}
	int nextId = 0;
	pRoot = ParseNode(nextId,*pScene->mRootNode);
}

void Model::Draw(Graphics& gfx) const
{
	if (auto node = pWindow->GetSelectedNode())
	{
		node->SetAppliedTransform(pWindow->GetTransform());
	}
	pRoot->Draw(gfx, dx::XMMatrixIdentity());
}

void Model::ShowWindow(const char* windowName)
{
	pWindow->Show(windowName, *pRoot);
}

void Model::SetRootTransform(DirectX::FXMMATRIX tf)
{
	pRoot->SetAppliedTransform(tf);
}

Model::~Model() noexcept
{}

std::unique_ptr<Mesh> Model::ParseMesh(Graphics& gfx, const aiMesh& mesh, MODEL_DESC desc)
{
	bool hasDiffuseMap = (desc.diffuse_path != "-1");
	bool hasSpecularMap = (desc.specular_path != "-1");
	bool hasNormalMap = (desc.normal_path != "-1");
	bool hasEmissiveMap = (desc.emission_path != "-1");


	namespace dx = DirectX;
	using dymvtx::VertexLayout;

	dymvtx::VertexBuffer vbuf(std::move(
		VertexLayout{}
		.Append(VertexLayout::Position3D)
		.Append(VertexLayout::Normal)
		.Append(VertexLayout::Tangent)
		.Append(VertexLayout::Bitangent)
		.Append(VertexLayout::Texture2D)

	));


	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		vbuf.EmplaceBack(
			dx::XMFLOAT3(mesh.mVertices[i].x * desc.scale, mesh.mVertices[i].y * desc.scale, mesh.mVertices[i].z * desc.scale),
			*reinterpret_cast<dx::XMFLOAT3*>(&mesh.mNormals[i]),
			*reinterpret_cast<dx::XMFLOAT3*>(&mesh.mTangents[i]),
			*reinterpret_cast<dx::XMFLOAT3*>(&mesh.mBitangents[i]),
			* reinterpret_cast<dx::XMFLOAT2*>(&mesh.mTextureCoords[0][i])
		);
	}

	std::vector<unsigned short> indices;
	indices.reserve(mesh.mNumFaces * 3);
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		const auto& face = mesh.mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}


	std::vector<std::shared_ptr<Bindable>> bindablePtrs;

	using namespace std::string_literals;
	if (hasDiffuseMap)
	{
		bindablePtrs.push_back(Texture::Resolve(gfx, desc.diffuse_path, 0));
	}
	if (hasSpecularMap)
	{
		bindablePtrs.push_back(Texture::Resolve(gfx, desc.specular_path, 1));
	}
	if (hasNormalMap)
	{
		bindablePtrs.push_back(Texture::Resolve(gfx, desc.normal_path, 2));
	}
	if (hasEmissiveMap)
	{
		bindablePtrs.push_back(Texture::Resolve(gfx, desc.emission_path, 3));
	}

	bindablePtrs.push_back(Sampler::Resolve(gfx));

	auto meshTag = desc.model_path + "%"s + mesh.mName.C_Str();


	bindablePtrs.push_back(VertexBuffer::Resolve(gfx, meshTag, vbuf));

	bindablePtrs.push_back(IndexBuffer::Resolve(gfx, meshTag, indices));
	 
	auto pvs = VertexShader::Resolve(gfx, "TexNormalPhongVS.cso");
	auto pvsbc = pvs->GetBytecode();
	bindablePtrs.push_back(std::move(pvs));


	bindablePtrs.push_back(InputLayout::Resolve(gfx, vbuf.GetLayout(), pvsbc));


	bindablePtrs.push_back(PixelShader::Resolve(gfx, "TexNormalSpecEmsPhongPS.cso"));
	//struct PSMaterialConstant
	//{
	//	float specularIntensity = 0.6f;
	//	float specularPower = 30.0f;
	//	BOOL  normalMapEnabled = TRUE;
	//	float padding[1];
	//} pmc;

	//bindablePtrs.push_back(PixelConstantBuffer<PSMaterialConstant>::Resolve(gfx, pmc, 1u));
	Dcb::RawLayout lay;
	lay.Add<Dcb::Bool>("hasDiffuseMap");
	lay.Add<Dcb::Bool>("hasSpecularMap");
	lay.Add<Dcb::Bool>("hasNormalMap");
	lay.Add<Dcb::Bool>("hasEmissiveMap");

	auto buf = Dcb::Buffer(std::move(lay));

	buf["hasDiffuseMap"] = hasDiffuseMap;
	buf["hasSpecularMap"] = hasSpecularMap;
	buf["hasNormalMap"] = hasNormalMap;
	buf["hasEmissiveMap"] = hasEmissiveMap;

	bindablePtrs.push_back(std::make_shared<NocachePixelConstantBufferEX>(gfx, buf, 7u));
	//bindablePtrs.push_back(std::make_shared<PixelConstantBuffer<PSMaps>>(gfx, psm, 7u));

	return std::make_unique<Mesh>(gfx, std::move(bindablePtrs));
}
std::unique_ptr<Node> Model::ParseNode(int& nextId, const aiNode& node)
{
	namespace dx = DirectX;
	const auto transform = dx::XMMatrixTranspose(dx::XMLoadFloat4x4(
		reinterpret_cast<const dx::XMFLOAT4X4*>(&node.mTransformation)
	));

	std::vector<Mesh*> curMeshPtrs;
	curMeshPtrs.reserve(node.mNumMeshes);
	for (size_t i = 0; i < node.mNumMeshes; i++)
	{
		const auto meshIdx = node.mMeshes[i];
		curMeshPtrs.push_back(meshPtrs.at(meshIdx).get());
	}

	auto pNode = std::make_unique<Node>(nextId++, node.mName.C_Str(), std::move(curMeshPtrs), transform);
	for (size_t i = 0; i < node.mNumChildren; i++)
	{
		pNode->AddChild(ParseNode(nextId, *node.mChildren[i]));
	}

	return pNode;
}
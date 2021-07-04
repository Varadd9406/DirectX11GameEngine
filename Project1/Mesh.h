#pragma once
#include "Drawable.h"
#include "BindableBasic.h"
#include "Vertex.h"
#include <optional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

enum textureTypes
{
	TEX_ALBEDO = 0x1,
	TEX_NORMAL = 0x2,
	TEX_SPECULAR = 0x3,
	TEX_EMISSIVITY = 0x4
};
struct MODEL_DESC
{
	float scale = 1.0f;
	std::string model_path = "-1";
	std::string diffuse_path = "-1";
	std::string normal_path = "-1";
	std::string specular_path = "-1";
	std::string emission_path = "-1";
};

class Mesh : public Drawable
{
public:
	Mesh(Graphics& gfx, std::vector<std::shared_ptr<Bindable>> bindPtrs);
	void Draw(Graphics& gfx, DirectX::FXMMATRIX accumulatedTransform) const ;
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	mutable DirectX::XMFLOAT4X4 transform;

};

class Node
{
	friend class Model;
public:
	Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform);
	void Draw(Graphics& gfx, DirectX::FXMMATRIX accumulatedTransform) const;
	void SetAppliedTransform(DirectX::FXMMATRIX transform);
	const DirectX::XMFLOAT4X4& GetAppliedTransform() const;
	int GetId() const;
	void ShowTree(Node*& pSelectedNode) const;
private:
	void AddChild(std::unique_ptr<Node> pChild);
private:
	std::string name;
	int id;
	std::vector<std::unique_ptr<Node>> childPtrs;
	std::vector<Mesh*> meshPtrs;
	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 appliedTransform;
};

class Model
{
public:
	Model(Graphics& gfx, MODEL_DESC desc);
	void Draw(Graphics& gfx) const;
	void ShowWindow(const char* windowName);
	void SetRootTransform(DirectX::FXMMATRIX tf);
	~Model() ;
private:
	static std::unique_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& mesh, MODEL_DESC model);
	std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node);
private:

	std::unique_ptr<Node> pRoot;
	std::vector<std::unique_ptr<Mesh>> meshPtrs;
	std::unique_ptr<class ModelWindow> pWindow;
};


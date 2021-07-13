#include "SolidSphere.h"
#include "BindableBasic.h"
#include "GraphicsThrowMacros.h"
#include "Sphere.h"
#include "Stencil.h"


SolidSphere::SolidSphere(Graphics& gfx, float radius)
{
	namespace dx = DirectX;
	using namespace bind;

	auto model = Sphere::Make();
	model.Transform(dx::XMMatrixScaling(radius, radius, radius));
	const auto geometryTag = "$sphere." + std::to_string(radius);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		auto solid = std::make_unique<Technique>();
		auto only = std::make_shared<Step>(0);

		auto pvs = VertexShader::Resolve(gfx, "SolidVS.cso");
		auto pvsbc = pvs->GetBytecode();
		only->AddBindable(std::move(pvs));

		only->AddBindable(PixelShader::Resolve(gfx, "SolidPS.cso"));

		struct PSColorConstant
		{
			dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
			float padding;
		} colorConst;
		only->AddBindable(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst, 1u));

		only->AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

		only->AddBindable(std::make_shared<TransformCbuf>(gfx));

		solid->AddStep(only);
		AddTechnique(std::move(solid));
	}
}

void SolidSphere::SetPos(DirectX::XMFLOAT3 pos)
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::GetTransformXM() const
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}
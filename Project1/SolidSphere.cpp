#include "SolidSphere.h"
#include "ConstantBuffers.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "Topology.h"
#include "TransformCbuf.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "GraphicsThrowMacros.h"
#include "Sphere.h"



SolidSphere::SolidSphere(Graphics& gfx, float radius)
{
	namespace dx = DirectX;

	auto model = Sphere::Make();
	model.Transform(dx::XMMatrixScaling(radius, radius, radius));
	const auto geometryTag = "$sphere." + std::to_string(radius);
	AddBind(bind::VertexBuffer::Resolve(gfx, geometryTag, model.vertices));
	AddBind(bind::IndexBuffer::Resolve(gfx, geometryTag, model.indices));

	auto pvs = bind::VertexShader::Resolve(gfx, "SolidVS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(bind::PixelShader::Resolve(gfx, "SolidPS.cso"));

	struct PSColorConstant
	{
		dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
		float padding;
	} colorConst;
	AddBind(bind::PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst,1u));

	AddBind(bind::InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

	AddBind(bind::Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_shared<bind::TransformCbuf>(gfx, *this));
}

void SolidSphere::SetPos(DirectX::XMFLOAT3 pos)
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::GetTransformXM() const
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}
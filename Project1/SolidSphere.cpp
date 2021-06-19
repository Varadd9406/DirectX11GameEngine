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
#include "Cube.h"



SolidSphere::SolidSphere(Graphics& gfx, float radius)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};
		IndexedTriangleList model = Sphere::Make<Vertex>();
		//model.Transform(dx::XMMatrixScaling(radius, radius, radius));
		AddBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"SolidVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddBind(std::move(pvs));

		AddBind(std::make_unique<PixelShader>(gfx, L"SolidPS.cso"));

		struct PSColorConstant
		{
			dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
			float padding;
		} colorConst;

		AddBind(std::make_unique<PixelConstantBuffer<PSColorConstant>>(gfx, colorConst));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

void SolidSphere::Update(float dt) {}

void SolidSphere::SetPos(DirectX::XMFLOAT3 pos)
{
	this->pos = pos;
}

DirectX::XMMATRIX SolidSphere::GetTransformXM() const
{
	return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}
#include "TransformCbuf.h"

namespace bind
{
	TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent, UINT slot)
		:
		parent(parent)
	{
		if (!pVcbuf)
		{
			pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx, slot);
		}
	}

	void TransformCbuf::Bind(Graphics& gfx)
	{
		UpdateBindImpl(gfx, GetTransforms(gfx));
	}

	void TransformCbuf::UpdateBindImpl(Graphics& gfx, const Transforms& tf)
	{
		pVcbuf->Update(gfx, tf);
		pVcbuf->Bind(gfx);
	}

	TransformCbuf::Transforms TransformCbuf::GetTransforms(Graphics& gfx)
	{
		const auto modelView = parent.GetTransformXM() * gfx.GetCamera();
		return {
			DirectX::XMMatrixTranspose(modelView),
			DirectX::XMMatrixTranspose(
				modelView *
				gfx.GetProjection()
			)
		};
	}

	std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::pVcbuf;

}
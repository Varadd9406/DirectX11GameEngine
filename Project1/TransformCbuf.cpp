#include "TransformCbuf.h"

namespace bind
{
	TransformCbuf::TransformCbuf(Graphics& gfx, UINT slot)
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

	void TransformCbuf::InitializeParentReference(const Drawable& parent)
	{
		pParent = &parent;
	}

	void TransformCbuf::UpdateBindImpl(Graphics& gfx, const Transforms& tf)
	{
		assert(pParent != nullptr);
		pVcbuf->Update(gfx, tf);
		pVcbuf->Bind(gfx);
	}

	TransformCbuf::Transforms TransformCbuf::GetTransforms(Graphics& gfx)
	{
		assert(pParent != nullptr);
		const auto modelView = pParent->GetTransformXM() * gfx.GetCamera();
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
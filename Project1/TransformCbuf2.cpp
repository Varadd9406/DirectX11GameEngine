#include "TransformCbuf2.h"

//namespace bind
//{
//	TransformCbuf2::TransformCbuf2(Graphics& gfx, const Drawable& parent, UINT slotV, UINT slotP)
//		:
//		TransformCbuf(gfx, parent, slotV)
//	{
//		if (!pPcbuf)
//		{
//			pPcbuf = std::make_unique<PixelConstantBuffer<Transforms>>(gfx, slotP);
//		}
//	}
//
//	void TransformCbuf2::Bind(Graphics& gfx) noexcept
//	{
//		const auto tf = GetTransforms(gfx);
//		TransformCbuf::UpdateBindImpl(gfx, tf);
//		UpdateBindImpl(gfx, tf);
//	}
//
//	void TransformCbuf2::UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept
//	{
//		pPcbuf->Update(gfx, tf);
//		pPcbuf->Bind(gfx);
//	}
//
//	std::unique_ptr<PixelConstantBuffer<TransformCbuf::Transforms>> TransformCbuf2::pPcbuf;
//}
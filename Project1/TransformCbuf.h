#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>
#include <memory>

namespace bind
{
	class TransformCbuf : public Bindable
	{
	protected:
		struct Transforms
		{
			DirectX::XMMATRIX modelView;
			DirectX::XMMATRIX modelViewProj;
		};
	public:
		TransformCbuf(Graphics& gfx, UINT slot = 0u);
		void Bind(Graphics& gfx) override;
		void InitializeParentReference(const Drawable& parent) override;
	protected:
		void UpdateBindImpl(Graphics& gfx, const Transforms& tf);
		Transforms GetTransforms(Graphics& gfx);

	private:
		static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
		const Drawable* pParent = nullptr;
	};
}
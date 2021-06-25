#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>
#include <memory>

class TransformCbuf : public Bindable
{
protected:
	struct Transforms
	{
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX modelViewProj;
	};
public:
	TransformCbuf(Graphics& gfx, const Drawable& parent,UINT slot = 0u);
	void Bind(Graphics& gfx) override;
protected:
	void UpdateBindImpl(Graphics& gfx, const Transforms& tf);
	Transforms GetTransforms(Graphics& gfx);

private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Drawable& parent;
};
#pragma once
#include "Drawable.h"

class SolidSphere : public Drawable
{
public:
	SolidSphere(Graphics& gfx, float radius);
	void SetPos(DirectX::XMFLOAT3 pos);
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
};
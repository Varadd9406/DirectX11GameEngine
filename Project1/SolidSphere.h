#pragma once
#include "DrawableBase.h"

class SolidSphere : public DrawableBase<SolidSphere>
{
public:
	SolidSphere(Graphics& gfx, float radius);
	void Update(float dt) override;
	void SetPos(DirectX::XMFLOAT3 pos);
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
};
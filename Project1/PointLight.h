#pragma once
#include "Graphics.h"
#include "SolidSphere.h"
#include "ConstantBuffers.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float radius = 0.5f);
	void SpawnControlWindow() ;
	void Reset() ;
	void Draw(Graphics& gfx) const ;
	void Bind(Graphics& gfx,DirectX::FXMMATRIX view) const ;
private:
	struct PointLightCBuf
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;

	};
private:
	PointLightCBuf cbData;
	mutable SolidSphere mesh;
	mutable bind::PixelConstantBuffer<PointLightCBuf> cbuf;
};

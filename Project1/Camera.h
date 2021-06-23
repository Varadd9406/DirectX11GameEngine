#pragma once
#include "Graphics.h"

class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetMatrix() const;
	void SpawnControlWindow() ;
	void Reset() ;
	//void Rotate(float dx, float dy) ;
	//void Translate(DirectX::XMFLOAT3 translation) ;
private:
	DirectX::XMFLOAT3 pos;
	float pitch;
	float yaw;
	static constexpr float travelSpeed = 12.0f;
	static constexpr float rotationSpeed = 0.004f;
};
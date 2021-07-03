#pragma once

#include <math.h>
#include <stringapiset.h>
#include <string>
#include <DirectXMath.h>



constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template <typename T>
constexpr auto sq(const T& x)
{
	return x * x;
}

template<typename T>
constexpr T wrap_angle(T theta)
{
	const T modded = fmod(theta, (T)2.0 * (T)PI_D);
	return (modded > (T)PI_D) ?
		(modded - (T)2.0 * (T)PI_D) :
		modded;
}

template<typename T>
constexpr T interpolate(const T& src, const T& dst, float alpha)
{
	return src + (dst - src) * alpha;
}

template<typename T>
constexpr T to_rad(T deg)
{
	return deg * PI / (T)180.0;
}


inline DirectX::XMFLOAT3 ExtractEulerAngles(const DirectX::XMFLOAT4X4& mat)
{
	DirectX::XMFLOAT3 euler;

	euler.x = asinf(-mat._32);                  // Pitch
	if (cosf(euler.x) > 0.0001)                // Not at poles
	{
		euler.y = atan2f(mat._31, mat._33);      // Yaw
		euler.z = atan2f(mat._12, mat._22);      // Roll
	}
	else
	{
		euler.y = 0.0f;                           // Yaw
		euler.z = atan2f(-mat._21, mat._11);     // Roll
	}

	return euler;
}

inline DirectX::XMFLOAT3 ExtractTranslation(const DirectX::XMFLOAT4X4& matrix)
{
	return { matrix._41,matrix._42,matrix._43 };
}


inline DirectX::XMMATRIX TransformationMatrix(float roll,float pitch,float yaw,float x,float y,float z)
{
	return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
		DirectX::XMMatrixTranslation(x, y, z);
}
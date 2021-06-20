#include "Texture.h"
#include "GraphicsThrowMacros.h"

#include <WICTextureLoader.h>
Texture::Texture(Graphics& gfx, std::wstring fileName)
{
	// create texture resource
	DirectX::CreateWICTextureFromFile
	(
		GetDevice(gfx),
		fileName.c_str(),
		nullptr,
		&pTextureView
	);
}

void Texture::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
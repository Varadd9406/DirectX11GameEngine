#include "Texture.h"
#include "GraphicsThrowMacros.h"
#include "Utility.h"
#include <WICTextureLoader.h>
Texture::Texture(Graphics& gfx, std::wstring fileName, unsigned int slot)
	:
	slot(slot)
{

	//string to wstring

	//wchar_t wstr[200];
	//mbtowc(NULL, NULL, 0);
	//mbtowc(wstr, fileName.c_str(), strlen(fileName.c_str()));
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
	GetContext(gfx)->PSSetShaderResources(slot, 1u, pTextureView.GetAddressOf());
}
#include "Texture.h"
#include "GraphicsThrowMacros.h"
#include "Utility.h"
#include <WICTextureLoader.h>
#include "BindableCodex.h"

namespace bind
{
	Texture::Texture(Graphics& gfx, std::string path, UINT slot)
		:
		path(path),
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
			GetContext(gfx),
			std::wstring{ path.begin(),path.end() }.c_str(),
			nullptr,
			&pTextureView
		);
	}

	void Texture::Bind(Graphics& gfx)
	{
		GetContext(gfx)->PSSetShaderResources(slot, 1u, pTextureView.GetAddressOf());
	}


	std::shared_ptr<Texture> Texture::Resolve(Graphics& gfx, const std::string& path, UINT slot)
	{
		return Codex::Resolve<Texture>(gfx, path, slot);
	}
	std::string Texture::GenerateUID(const std::string& path, UINT slot)
	{
		using namespace std::string_literals;
		return typeid(Texture).name() + "#"s + path + "#" + std::to_string(slot);
	}
	std::string Texture::GetUID() const
	{
		return GenerateUID(path, slot);
	}
}
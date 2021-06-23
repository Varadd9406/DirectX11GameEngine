#pragma once

#include "Bindable.h"
#include<memory>

class Texture : public Bindable
{
public:
	Texture(Graphics& gfx, std::string path, UINT slot = 0);
	void Bind(Graphics& gfx) override;
	static std::shared_ptr<Texture> Resolve(Graphics& gfx, const std::string& path, UINT slot = 0);
	static std::string GenerateUID(const std::string& path, UINT slot = 0);
	std::string GetUID() const override;
private:
	unsigned int slot;
protected:
	std::string path;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};
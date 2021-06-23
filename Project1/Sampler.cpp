#include "Sampler.h"
#include "GraphicsThrowMacros.h"
#include "BindableCodex.h"


Sampler::Sampler(Graphics& gfx)
{
	INFOMAN(gfx);

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	DX_EXCEPT_THROW(GetDevice(gfx)->CreateSamplerState(&samplerDesc, &pSampler));
}

void Sampler::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}

std::shared_ptr<Sampler> Sampler::Resolve(Graphics& gfx)
{
	return Codex::Resolve<Sampler>(gfx);
}
std::string Sampler::GenerateUID()
{
	return typeid(Sampler).name();
}
std::string Sampler::GetUID() const 
{
	return GenerateUID();
}
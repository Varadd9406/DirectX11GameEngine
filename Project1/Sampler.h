#pragma once
#include "Bindable.h"
#include <memory>

class Sampler : public Bindable
{
public:
	Sampler(Graphics& gfx);
	void Bind(Graphics& gfx) override;
	static std::shared_ptr<Sampler> Resolve(Graphics& gfx);
	static std::string GenerateUID();
	std::string GetUID() const override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};
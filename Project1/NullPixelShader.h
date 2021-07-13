#pragma once
#include "Bindable.h"
#include <memory>
namespace bind
{
	class NullPixelShader : public Bindable
	{
	public:
		NullPixelShader(Graphics& gfx);
		void Bind(Graphics& gfx) override;
		static std::shared_ptr<NullPixelShader> Resolve(Graphics& gfx);
		static std::string GenerateUID();
		std::string GetUID() const override;
	};
}
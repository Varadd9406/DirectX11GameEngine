#pragma once
#include "Graphics.h"
#include "TechniqueProbe.h"
class Drawable;


namespace bind
{
	class Bindable
	{
	public:
		virtual void Bind(Graphics& gfx)  = 0;
		virtual std::string GetUID() const 
		{
			assert(false);
			return "";
		}
		virtual void InitializeParentReference(const Drawable&) {}
		virtual void Accept(class TechniqueProbe&) {}
		virtual ~Bindable() = default;
	protected:
		static ID3D11DeviceContext* GetContext(Graphics& gfx);
		static ID3D11Device* GetDevice(Graphics& gfx);
		static DxgiManager& GetInfoManager(Graphics& gfx);
	};
}
#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) 
{
	return gfx.pContext.Get();
}

ID3D11Device* Bindable::GetDevice(Graphics& gfx) 
{
	return gfx.pDevice.Get();
}

DxgiManager& Bindable::GetInfoManager(Graphics& gfx)
{
	return gfx.infoManager;
}
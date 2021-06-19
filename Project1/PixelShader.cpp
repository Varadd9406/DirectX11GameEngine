#include "PixelShader.h"
#include "GraphicsThrowMacros.h"

PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	DX_EXCEPT_THROW(D3DReadFileToBlob(path.c_str(), &pBlob));
	DX_EXCEPT_THROW(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
}

void PixelShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
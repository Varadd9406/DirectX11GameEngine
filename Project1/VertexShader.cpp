#include "VertexShader.h"
#include "GraphicsThrowMacros.h"


VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);

	DX_EXCEPT_THROW(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));
	DX_EXCEPT_THROW(GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	));
}

void VertexShader::Bind(Graphics& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const
{
	return pBytecodeBlob.Get();
}
#include "VertexShader.h"
#include "GraphicsThrowMacros.h"
#include "BindableCodex.h"

namespace bind
{
	VertexShader::VertexShader(Graphics& gfx, const std::string& path)
	{
		INFOMAN(gfx);

		DX_EXCEPT_THROW(D3DReadFileToBlob(std::wstring{ path.begin(),path.end() }.c_str(), &pBytecodeBlob));
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

	std::shared_ptr<VertexShader> VertexShader::Resolve(Graphics& gfx, const std::string& path)
	{
		return Codex::Resolve<VertexShader>(gfx, path);
	}
	std::string VertexShader::GenerateUID(const std::string& path)
	{
		using namespace std::string_literals;
		return typeid(VertexShader).name() + "#"s + path;
	}
	std::string VertexShader::GetUID() const noexcept
	{
		return GenerateUID(path);
	}
}
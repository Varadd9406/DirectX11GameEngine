#include "InputLayout.h"
#include "GraphicsThrowMacros.h"
#include "BindableCodex.h"

InputLayout::InputLayout(Graphics& gfx,
	dymvtx::VertexLayout layout_in,
	ID3DBlob* pVertexShaderBytecode)
	:
	layout(layout_in)
{
	INFOMAN(gfx);
	const auto d3dLayout = layout.GetD3DLayout();

	DX_EXCEPT_THROW(GetDevice(gfx)->CreateInputLayout(
		d3dLayout.data(), (UINT)d3dLayout.size(),
		pVertexShaderBytecode->GetBufferPointer(),
		pVertexShaderBytecode->GetBufferSize(),
		&pInputLayout
	));
}

void InputLayout::Bind(Graphics& gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}

std::shared_ptr<InputLayout> InputLayout::Resolve(Graphics& gfx,
	const dymvtx::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode)
{
	return Codex::Resolve<InputLayout>(gfx, layout, pVertexShaderBytecode);
}
std::string InputLayout::GenerateUID(const dymvtx::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode)
{
	using namespace std::string_literals;
	return typeid(InputLayout).name() + "#"s + layout.GetCode();
}
std::string InputLayout::GetUID() const noexcept
{
	return GenerateUID(layout);
}
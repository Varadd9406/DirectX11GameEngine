#pragma once
#include "Bindable.h"
#include "Vertex.h"
#include <memory>
namespace bind
{
	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx,
			dymvtx::VertexLayout layout,
			ID3DBlob* pVertexShaderBytecode);
		void Bind(Graphics& gfx) override;
		static std::shared_ptr<InputLayout> Resolve(Graphics& gfx,
			const dymvtx::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode);
		static std::string GenerateUID(const dymvtx::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode = nullptr);
		std::string GetUID() const noexcept override;
	protected:
		dymvtx::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}

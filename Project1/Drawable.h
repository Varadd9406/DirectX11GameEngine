#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include <DirectXMath.h>
#include <memory>
#include "IndexBuffer.h"

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	void Draw(Graphics& gfx) const ;
	virtual ~Drawable() = default;
protected:
	void AddBind(std::shared_ptr<Bindable> bind);
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::shared_ptr<Bindable>> binds;
};
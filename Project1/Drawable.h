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
	template<class T>
	T* QueryBindable()
	{
		for (auto& pb : binds)
		{
			if (auto pt = dynamic_cast<T*>(pb.get()))
			{
				return pt;
			}
		}
		return nullptr;
	}
	void AddBind(std::shared_ptr<bind::Bindable> bind);
private:
	const bind::IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::shared_ptr<bind::Bindable>> binds;
};
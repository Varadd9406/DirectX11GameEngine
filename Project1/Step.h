#pragma once
#include <vector>
#include <memory>
#include "Bindable.h"

class Step
{
public:
	Step(size_t targetPass_in)
		:
		targetPass{ targetPass_in }
	{}
	//template<class B>
	//B* QueryBindable() noexcept
	//{
	//	for( auto& pb : binds )
	//	{
	//		if( auto pt = dynamic_cast<T*>(pb.get()) )
	//		{
	//			return pt;
	//		}
	//	}
	//	return nullptr;
	//}
	void AddBindable(std::shared_ptr<bind::Bindable> bind_in) 
	{
		bindables.push_back(std::move(bind_in));
	}
	void Bind(class Graphics& gfx) const
	{
		for (auto b : bindables)
		{
			b->Bind(gfx);
		}
	}
	void InitializeParentReferences(const class Drawable& parent);
public:
	size_t targetPass;
private:
	std::vector<std::shared_ptr<bind::Bindable>> bindables;
};
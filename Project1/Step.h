#pragma once
#include <vector>
#include <memory>
#include "Bindable.h"
#include "TechniqueProbe.h"

class Step
{
public:
	Step(size_t targetPass_in)
		:
		targetPass{ targetPass_in }
	{}
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

	void Accept(TechniqueProbe& probe)
	{
		probe.SetStep(this);
		for (auto& pb : bindables)
		{
			pb->Accept(probe);
		}
	}
public:
	size_t targetPass;
private:
	std::vector<std::shared_ptr<bind::Bindable>> bindables;
};
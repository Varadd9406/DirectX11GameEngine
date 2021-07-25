#pragma once
#include "Step.h"
#include <vector>

class Technique
{
public:
	Technique() = default;
	Technique(std::string name)
		:
		name(name)
	{}
	void Submit(class FrameCommander& frame, class Drawable& drawable);
	void AddStep(std::shared_ptr<Step> step)
	{
		steps.push_back(step);
	}
	bool IsActive()
	{
		return active;
	}
	void SetActiveState(bool active_in)
	{
		active = active_in;
	}
	void InitializeParentReferences(Drawable& parent) ;
	void Accept(TechniqueProbe& probe)
	{
		probe.SetTechnique(this);
		for (auto& s : steps)
		{
			s->Accept(probe);
		}
	}
	const std::string& GetName() const
	{
		return name;
	}
private:
	bool active = true;
	std::vector<std::shared_ptr<Step>> steps;
	std::string name = "No name tech";
};
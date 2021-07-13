#pragma once
#include "Step.h"
#include <vector>


class Technique
{
public:
	void Submit(class FrameCommander& frame, class Drawable& drawable);
	void AddStep(std::shared_ptr<Step> step)
	{
		steps.push_back(step);
	}
	void Activate()
	{
		active = true;
	}
	void Deactivate() 
	{
		active = false;
	}
	void InitializeParentReferences(Drawable& parent) ;
private:
	bool active = true;
	std::vector<std::shared_ptr<Step>> steps;
};
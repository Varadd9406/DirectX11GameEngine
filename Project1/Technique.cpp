#include "Technique.h"
#include "FrameCommander.h"

void Technique::Submit(FrameCommander& frame, class Drawable& drawable)
{
	if (active)
	{
		for (auto& step : steps)
		{
			frame.Submit(step,drawable);
		}
	}
}

void Technique::InitializeParentReferences(class Drawable& parent)
{
	for (auto& s : steps)
	{
		s->InitializeParentReferences(parent);
	}
}
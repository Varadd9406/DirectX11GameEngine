#include "Step.h"

void Step::InitializeParentReferences(const class Drawable& parent)
{
	for (auto& b : bindables)
	{
		b->InitializeParentReference(parent);
	}
}

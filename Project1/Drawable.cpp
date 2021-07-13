#include "Drawable.h"
#include "GraphicsThrowMacros.h"
#include "IndexBuffer.h"
#include <cassert>
#include <typeinfo>
#include "FrameCommander.h"
void Drawable::Submit(FrameCommander& frame)
{
	for (auto tech : techniques)
	{
		tech->Submit(frame,*this );
	}
}


void Drawable::AddTechnique(std::unique_ptr<Technique> tech_in)
{
	tech_in->InitializeParentReferences(*this);
	techniques.push_back(std::move(tech_in));
}

void Drawable::Bind(Graphics& gfx) 
{
	pTopology->Bind(gfx);
	pIndices->Bind(gfx);
	pVertices->Bind(gfx);
}

UINT Drawable::GetIndexCount()
{
	return pIndices->GetCount();
}

Drawable::~Drawable()
{}
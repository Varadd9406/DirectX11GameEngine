#include "Job.h"
#include "Drawable.h"
#include "Step.h"
#include "Graphics.h"

Job::Job(std::shared_ptr<Step> pStep, Drawable* pDrawable)
	:
	mDrawable{ pDrawable },
	mStep{ pStep }
{}

void Job::Execute(Graphics& gfx) const 
{
	mDrawable->Bind(gfx);
	mStep->Bind(gfx);
	gfx.DrawIndexed(mDrawable->GetIndexCount());
}
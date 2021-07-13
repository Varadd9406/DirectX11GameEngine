#pragma once
#include <memory>
class Job
{
public:
	Job(std::shared_ptr<class Step> pStep, class Drawable* pDrawable);
	void Execute(class Graphics& gfx) const;
private:
	Drawable* mDrawable;
	std::shared_ptr<Step> mStep;
};
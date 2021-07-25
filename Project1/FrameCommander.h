#pragma once
#include <array>
#include "BindableBasic.h"
#include "Graphics.h"
#include "Step.h"
#include "Job.h"
#include "Pass.h"
#include <memory>
class FrameCommander
{
public:
	void Accept(Job job, size_t target)
	{
		passes[target].Accept(job);
	}
	void Execute(Graphics& gfx) const 
	{
		using namespace bind;
		// normally this would be a loop with each pass defining it setup / etc.
		// and later on it would be a complex graph with parallel execution contingent
		// on input / output requirements

		// main phong lighting pass
		Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
		passes[0].Execute(gfx);
		// outline masking pass
		Stencil::Resolve(gfx, Stencil::Mode::Write)->Bind(gfx);
		NullPixelShader::Resolve(gfx)->Bind(gfx);
		passes[1].Execute(gfx);
		//outline drawing pass
		Stencil::Resolve(gfx, Stencil::Mode::Mask)->Bind(gfx);
		passes[2].Execute(gfx);
	}
	void Reset()
	{
		for (auto& p : passes)
		{
			p.Reset();
		}
	}
	void Submit(std::shared_ptr<Step> step_in,Drawable& drawable_in)
	{
		Accept(std::move(Job(step_in, &drawable_in)), step_in->targetPass);
	}

private:
	std::array<Pass, 3> passes;
};
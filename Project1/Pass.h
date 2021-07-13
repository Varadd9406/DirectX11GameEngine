#pragma once
#include "Graphics.h"
#include "Job.h"
#include <vector>

class Pass
{
public:
	void Accept(Job job)
	{
		jobs.push_back(job);
	}
	void Execute(Graphics& gfx) const
	{
		for (auto j : jobs)
		{
			j.Execute(gfx);
		}
	}
	void Reset()
	{
		jobs.clear();
		jobs.shrink_to_fit();
	}
private:
	std::vector<Job> jobs;
};

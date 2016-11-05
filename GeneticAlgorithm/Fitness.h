#pragma once

#include <vector>

namespace GA
{
	class Fitness
	{
	public:
		virtual int forGenotype(std::vector<int>& genotype) = 0;
	};
}
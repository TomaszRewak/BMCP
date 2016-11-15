#pragma once

#include <random>

namespace BMCP_GA
{
	class Random
	{
	private:
		std::random_device rd;
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;

	public:
		Random() :
			rd(),
			generator(rd())
		{ }

		double uniform()
		{
			return distribution(generator);
		}

		int range(int max)
		{
			return distribution(generator) * max;
		}
	};
}
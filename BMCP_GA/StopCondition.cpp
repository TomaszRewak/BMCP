// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <algorithm>

#include "StopCondition.h"
#include "GeneticAlgorithm\GeneticAlgorithm.h"

namespace BMCP_GA
{
	GenerationsStopCondition::GenerationsStopCondition(int generations) :
		generations(generations)
	{ }

	bool GenerationsStopCondition::checkCondition(GA::GeneticAlgorithm& geneticAlgorithm)
	{
		return geneticAlgorithm.currentGeneration() >= generations;
	}

	TimeStopCondition::TimeStopCondition(int maxTime) :
		maxTime(maxTime)
	{ }

	void TimeStopCondition::reset(GA::GeneticAlgorithm& geneticAlgorithm)
	{
		start = std::chrono::steady_clock::now();
	}

	bool TimeStopCondition::checkCondition(GA::GeneticAlgorithm& geneticAlgorithm)
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() > maxTime;
	}

	LongTailStopCondition::LongTailStopCondition(int maxTime, double tailFactor) :
		maxTime(maxTime),
		tailFactor(tailFactor)
	{ }

	void LongTailStopCondition::reset(GA::GeneticAlgorithm& geneticAlgorithm)
	{
		prevBest = INT_MAX;
		prevBestGeneration = 0;
		tailLength = 1;

		start = std::chrono::steady_clock::now();
	}

	bool LongTailStopCondition::checkCondition(GA::GeneticAlgorithm& geneticAlgorithm)
	{
		if (geneticAlgorithm.globalBest.fitness < prevBest)
		{
			prevBest = geneticAlgorithm.globalBest.fitness;
			tailLength = std::max(tailLength, (int)(tailFactor * (geneticAlgorithm.currentGeneration() - prevBestGeneration)));
			prevBestGeneration = geneticAlgorithm.currentGeneration();
		}

		return
			std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() > maxTime
			&&
			geneticAlgorithm.currentGeneration() > prevBestGeneration + tailLength;
	}
}
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <algorithm>
#include <climits>

#include "StopCondition.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"

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

	bool TimeStopCondition::checkCondition(GA::GeneticAlgorithm& ga)
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - ga.startTime).count() > maxTime;
	}

	LongTailStopCondition::LongTailStopCondition(int maxTime, double tailFactor) :
		maxTime(maxTime),
		tailFactor(tailFactor)
	{
		prevBest = INT_MAX;
		prevBestGeneration = 0;
		tailLength = 1;
	}

	bool LongTailStopCondition::checkCondition(GA::GeneticAlgorithm& ga)
	{
		if (ga.globalBest.fitness < prevBest)
		{
			prevBest = ga.globalBest.fitness;
			tailLength = std::max(tailLength, (int)(tailFactor * (ga.currentGeneration() - prevBestGeneration)));
			prevBestGeneration = ga.currentGeneration();
		}

		return
			std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - ga.startTime).count() > maxTime
			&&
			ga.currentGeneration() > prevBestGeneration + tailLength;
	}
}
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "StopCondition.h"

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
}
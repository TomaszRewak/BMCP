// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

namespace GA
{
	class GeneticAlgorithm;

	class StopCondition
	{
	public:
		virtual void reset(GeneticAlgorithm& geneticAlgorithm);
		virtual bool checkCondition(GeneticAlgorithm& geneticAlgorithm) = 0;
	};
}
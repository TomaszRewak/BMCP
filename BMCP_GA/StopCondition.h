// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <ctime>
#include <chrono>

#include "GeneticAlgorithm\GeneticAlgorithm.h"
#include "GeneticAlgorithm\StopCondition.h"

namespace BMCP_GA
{
	class GenerationsStopCondition : public GA::StopCondition
	{
	private:
		int generations;

	public:
		GenerationsStopCondition(int generations);

		virtual bool checkCondition(GA::GeneticAlgorithm& geneticAlgorithm);
	};

	class TimeStopCondition : public GA::StopCondition
	{
	private:
		int maxTime;

	public:
		TimeStopCondition(int maxTime);

		virtual bool checkCondition(GA::GeneticAlgorithm& geneticAlgorithm) override;
	};

	class LongTailStopCondition : public GA::StopCondition
	{
	private:
		int maxTime;
		double tailFactor;

		int prevBest;
		int prevBestGeneration;

		int tailLength;

	public:
		LongTailStopCondition(int minTime, double tailFactor);

		virtual bool checkCondition(GA::GeneticAlgorithm& geneticAlgorithm) override;
	};
}
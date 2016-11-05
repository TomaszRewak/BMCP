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
		std::chrono::steady_clock::time_point start;

	public:
		TimeStopCondition(int maxTime);

		virtual void reset(GA::GeneticAlgorithm& geneticAlgorithm);
		virtual bool checkCondition(GA::GeneticAlgorithm& geneticAlgorithm);
	};
}
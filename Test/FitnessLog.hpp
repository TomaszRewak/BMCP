// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <algorithm>
#include <string>
#include <iostream>

#include "GeneticAlgorithm\Component.h"

class FitnessLogScope
{
public:
	int globalmin = INT_MAX;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
};

class FitnessLog : public GA::Component
{
private:
	FitnessLogScope& logScope;

public:
	FitnessLog(FitnessLogScope& logScope) :
		logScope(logScope)
	{ }

	virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override
	{
		int minValue = INT_MAX;
		int avgValue = 0;
		int maxValue = INT_MIN;

		for (auto& specimen : ga.population)
		{
			minValue = std::min(minValue, specimen.fitness);
			avgValue += specimen.fitness;
			maxValue = std::max(maxValue, specimen.fitness);
		}
		avgValue /= ga.population.size();

		int time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - logScope.start).count();

		if (logScope.globalmin == INT_MAX)
			logScope.globalmin = minValue + 5;

		while (minValue < logScope.globalmin)
		{
			logScope.globalmin--;

			std::string globalMinLog = std::to_string(ga.currentGeneration()) + "\t" + std::to_string(time) + "\t" + std::to_string(logScope.globalmin);
			ga.addLog("fitness_global", globalMinLog);
			std::cout << globalMinLog << std::endl;
		}

		//std::string log = std::to_string(ga.currentGeneration()) + "\t" + std::to_string(time) + "\t" + std::to_string(minValue) + "\t" + std::to_string(avgValue) + "\t" + std::to_string(maxValue);
		//ga.addLog("fitness", log);

		if (chain)
			return chain->get(ga);
	}
};
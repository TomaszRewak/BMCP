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

class FitnessLog : public GA::Component
{
private:
	int globalmin = INT_MAX;
	int minValue; 
	int avgValue; 
	int maxValue;

	std::chrono::steady_clock::time_point start;

public:
	virtual void reset(GA::GeneticAlgorithm& ga)
	{
		start = std::chrono::steady_clock::now();
	}

	virtual void prepare(GA::GeneticAlgorithm& ga)
	{
		minValue = INT_MAX;
		avgValue = 0;
		maxValue = INT_MIN;
	}

	virtual GA::Specimen get(GA::ComponentChain componentChain)
	{
		auto specimen = componentChain.get();

		minValue = std::min(minValue, specimen.fitness);
		avgValue += specimen.fitness;
		maxValue = std::max(maxValue, specimen.fitness);

		return std::move(specimen);
	}

	virtual void log(GA::GeneticAlgorithm& ga)
	{
		int time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();

		avgValue /= ga.population.size();

		std::string log = std::to_string(ga.currentGeneration()) + "\t" + std::to_string(time) + "\t" + std::to_string(minValue) + "\t"; // +std::to_string(avgValue) + "\t" + std::to_string(maxValue);

		//ga.addLog("fitness", log);

		if (minValue < globalmin)
		{
			ga.addLog("fitness_global", log);
			globalmin = minValue;

			std::cout << log << std::endl;
		}
	}
};
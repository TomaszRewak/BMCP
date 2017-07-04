// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <climits>

#include "../BMCP_GA/Fitness.h"

class FitnessLogScope
{
public:
	int globalmin = INT_MAX;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
};

class FitnessLog : public GA::Component
{
private:
	BMCP::Greedy greedy;
	FitnessLogScope& logScope;

public:
	FitnessLog(BMCP::Graph& graph, FitnessLogScope& logScope) :
		greedy(BMCP::Greedy(graph)),
		logScope(logScope)
	{ }

	virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override
	{
		auto specimen = chain->get(ga);

		int minValue = INT_MAX;
		//int avgValue = 0;
		//int maxValue = INT_MIN;

		for (auto& specimen : ga.population)
		{
			int vaule = greedy.rate(specimen.genotype);
			//int vaule = specimen.fitness;

			minValue = std::min(minValue, vaule);
			//avgValue += vaule;
			//maxValue = std::max(maxValue, vaule);
		}
		//avgValue /= ga.population.size();

		//std::cout << minValue << " " << logScope.globalmin << std::endl;

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

		return specimen;
	}
};
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <memory>
#include <vector>
#include <algorithm>

#include "GeneticAlgorithm.h"
#include "InitialPopulation.h"
#include "StopCondition.h"
#include "Fitness.h"
#include "Specimen.h"
#include "Component.h"

namespace GA
{
	void GeneticAlgorithm::start()
	{
		startTime = std::chrono::steady_clock::now();

		for (auto spec : initialPopulation->generate())
			population.push_back(std::move(spec));

		for (auto& specimen : population)
			if (specimen.fitness <= globalBest.fitness)
				globalBest = specimen;

		while(true)
		{
			for (auto stopCondition : stopConditions)
				if (stopCondition->checkCondition(*this))
					return;

			for (auto chainGenerator : chainGenerators)
			{
				ComponentChainBuilder builder;
				chainGenerator(builder);

				builder.chain->get(*this);
			}

			for (auto& specimen : population)
				if (specimen.fitness <= globalBest.fitness)
					globalBest = specimen;

			generation++;
		}
	}

	int GeneticAlgorithm::currentGeneration()
	{
		return generation;
	}

	void GeneticAlgorithm::addLog(std::string category, std::string log)
	{
		logs[category].push_back(log);
	}

#pragma region Initialization

	GeneticAlgorithm& GeneticAlgorithm::withInitialPopulation(std::shared_ptr<InitialPopulation> initialPopulation)
	{
		this->initialPopulation = initialPopulation;
		return *this;
	}

	GeneticAlgorithm& GeneticAlgorithm::withStopCondition(std::shared_ptr<StopCondition> stopCondition)
	{
		stopConditions.push_back(stopCondition);
		return *this;
	}

	GeneticAlgorithm& GeneticAlgorithm::with(std::function<void(ComponentChainBuilder& builder)> chain)
	{
		chainGenerators.push_back(chain);
		return *this;
	}

#pragma endregion

}
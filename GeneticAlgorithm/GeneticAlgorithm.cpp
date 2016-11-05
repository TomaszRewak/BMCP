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
#include "Selection.h"
#include "StopCondition.h"
#include "Fitness.h"
#include "Specimen.h"
#include "Component.h"

namespace GA
{
	void GeneticAlgorithm::start()
	{
		for (auto spec : initialPopulation->generate())
			population.push_back(std::move(spec));

		for (auto& specimen : population)
			if (specimen.fitness < globalBest.fitness)
				globalBest = specimen;

		for (auto stopCondition : stopConditions)
			stopCondition->reset(*this);

		for (auto component : components)
			component->reset(*this);

		while(true)
		{
			for (auto stopCondition : stopConditions)
				if (stopCondition->checkCondition(*this))
					return;

			for (auto& component : components)
				component->prepare(*this);

			ComponentChain chain = ComponentChain(*this, components.rbegin(), components.rend());

			std::vector<Specimen> newPopulation;
			newPopulation.reserve(population.size());

			while (newPopulation.size() < population.size())
				newPopulation.push_back(std::move(chain.get()));

			population = std::move(newPopulation);

			for (auto& specimen : population)
				if (specimen.fitness < globalBest.fitness)
					globalBest = specimen;

			for (auto& component : components)
				component->log(*this);

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

	GeneticAlgorithm GeneticAlgorithm::withInitialPopulation(std::shared_ptr<InitialPopulation> initialPopulation)
	{
		auto newBuilder = *this;
		newBuilder.initialPopulation = initialPopulation;
		return newBuilder;
	}

	GeneticAlgorithm GeneticAlgorithm::withStopCondition(std::shared_ptr<StopCondition> stopCondition)
	{
		auto newBuilder = *this;
		newBuilder.stopConditions.push_back(stopCondition);
		return newBuilder;
	}

	GeneticAlgorithm GeneticAlgorithm::with(std::shared_ptr<Component> component)
	{
		auto newBuilder = *this;
		newBuilder.components.push_back(component);
		return newBuilder;
	}

#pragma endregion

}
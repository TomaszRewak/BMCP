// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <map>
#include <functional>
#include <chrono>

#include "Component.h"
#include "Specimen.h"
#include "Fitness.h"
#include "StopCondition.h"
#include "InitialPopulation.h"

namespace GA
{
	class GeneticAlgorithm
	{
	private:
		std::shared_ptr<InitialPopulation> initialPopulation;
		std::vector<std::shared_ptr<StopCondition>> stopConditions;
		std::vector<std::function<void(ComponentChainBuilder& builder)>> chainGenerators;

		int generation = 0;
		
	public:
		std::vector<Specimen> population;
		Specimen globalBest;

		std::chrono::steady_clock::time_point startTime;

		void start();
		int currentGeneration();

		std::map<std::string, std::vector<std::string>> logs;
		void addLog(std::string category, std::string log);

#pragma region Initialization

	public:
		GeneticAlgorithm& withInitialPopulation(std::shared_ptr<InitialPopulation> initlaPopulation);
		GeneticAlgorithm& withStopCondition(std::shared_ptr<StopCondition> stopCondition);
		GeneticAlgorithm& with(std::function<void(ComponentChainBuilder& builder)> chain);

		template<typename T, typename... Args>
		GeneticAlgorithm& withInitialPopulation(Args&&... args) { return withInitialPopulation(std::make_shared<T>(std::forward<Args>(args)...)); }
		template<typename T, typename... Args>
		GeneticAlgorithm& withStopCondition(Args&&... args) { return withStopCondition(std::make_shared<T>(std::forward<Args>(args)...)); }
	};

#pragma endregion

}
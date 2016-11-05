// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <vector>
#include <memory>

#include "GeneticAlgorithm.h"
#include "Component.h"
#include "StopCondition.h"
#include "Fitness.h"
#include "InitialPopulation.h"

namespace GA
{
	class Builder
	{
	private:
		std::shared_ptr<InitialPopulation> initialPopulation;
		std::shared_ptr<Selection> selection;
		std::vector<std::shared_ptr<Fitness>> fitnesses;
		std::vector<std::shared_ptr<Component>> components;
		std::vector<std::shared_ptr<StopCondition>> stopConditions;

	public:
		static GeneticAlgorithm std();
	};
}
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "../GeneticAlgorithm/Component.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"
#include "../BMCP/Greedy.h"

#include "Random.h"

namespace BMCP_GA
{
	class Fitness : public GA::Component
	{
	private:
		BMCP::Greedy greedy;

	public:
		Fitness(BMCP::Graph& graph);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class NeighbourhoodFitness : public GA::Component
	{
	private:
		BMCP::Greedy greedy;
		int neighbourhood;

		Random random;

	public:
		NeighbourhoodFitness(BMCP::Graph& graph, int neighbourhood);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "../GeneticAlgorithm/InitialPopulation.h"
#include "../BMCP/Graph.h"
#include "../BMCP/Greedy.h"

namespace BMCP_GA
{
	class InitialPopulation : public GA::InitialPopulation
	{
	private:
		BMCP::Greedy greedy;

		size_t genotypeLenght;
		size_t size;

		std::vector<int> genotypeStructure;

	public:
		InitialPopulation(BMCP::Graph& graph, size_t size);

		virtual std::vector<GA::Specimen> generate() override;
	};

	class InitialPopulationWithoutRating : public GA::InitialPopulation
	{
	private:
		size_t genotypeLenght;
		size_t size;

		std::vector<int> genotypeStructure;

	public:
		InitialPopulationWithoutRating(BMCP::Graph& graph, size_t size);

		virtual std::vector<GA::Specimen> generate() override;
	};
}
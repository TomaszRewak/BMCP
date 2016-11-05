// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <algorithm>

#include "InitialPopulation.h"

namespace BMCP_GA
{
	InitialPopulation::InitialPopulation(BMCP::Graph& graph, size_t size) :
		greedy(graph),
		genotypeLenght(graph.slots),
		size(size)
	{
		genotypeStructure.resize(graph.nodes.size());

		for (size_t i = 0; i < graph.nodes.size(); i++)
		{
			genotypeStructure[i] = graph.nodes[i].weight;
		}
	}

	std::vector<GA::Specimen> InitialPopulation::generate()
	{
		std::vector<GA::Specimen> population;
		population.reserve(size);

		for (int i = 0; i < size; i++)
		{
			GA::Specimen specimen;
			std::vector<int>& genotype = specimen.genotype;
			genotype.reserve(genotypeLenght);

			for (int n = 0; n < genotypeStructure.size(); n++)
				for (int j = 0; j < genotypeStructure[n]; j++)
					genotype.push_back(n);

			std::random_shuffle(genotype.begin(), genotype.end());

			specimen.fitness = greedy.rate(genotype);

			population.push_back(specimen);
		}
		
		return std::move(population);
	}
}
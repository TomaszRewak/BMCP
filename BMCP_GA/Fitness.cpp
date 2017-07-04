// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Fitness.h"

namespace BMCP_GA
{
	Fitness::Fitness(BMCP::Graph& graph) :
		greedy(BMCP::Greedy(graph))
	{ }

	GA::Specimen Fitness::get(GA::GeneticAlgorithm& ga)
	{
		auto specimen = chain->get(ga);

		specimen.fitness = greedy.rate(specimen.genotype);

		return std::move(specimen);
	}

	NeighbourhoodFitness::NeighbourhoodFitness(BMCP::Graph& graph, int neighbourhood) :
		greedy(BMCP::Greedy(graph)), neighbourhood(neighbourhood)
	{ }

	GA::Specimen NeighbourhoodFitness::get(GA::GeneticAlgorithm& ga)
	{
		auto specimen = chain->get(ga);

		int baseFitness = greedy.rate(specimen.genotype);
		specimen.fitness = baseFitness * (neighbourhood + 1);

		for (int i = 0; i < neighbourhood; i++)
		{
			auto neighbour = specimen.genotype;

			auto begin = neighbour.begin() + neighbour.size() * random.uniform();
			auto end = neighbour.begin() + neighbour.size() * random.uniform();
			if (begin > end) std::swap(begin, end);
			std::rotate(begin, begin + 1, end + 1);

			if (greedy.rate(neighbour) > baseFitness)
				specimen.fitness++;
		}

		return std::move(specimen);
	}
}
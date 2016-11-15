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
}
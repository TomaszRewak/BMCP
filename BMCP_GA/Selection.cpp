// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Selection.h"

namespace BMCP_GA
{
	RingSelection::RingSelection(int ringSize) :
		ringSize(ringSize)
	{ }

	GA::Specimen RingSelection::get(GA::GeneticAlgorithm& ga)
	{
		GA::Specimen bestSpecimen;

		for (int i = 0; i < ringSize; i++) 
		{
			GA::Specimen specimen = chain ? chain->get(ga) : ga.population[random.range(ga.population.size())];

			if (specimen.fitness < bestSpecimen.fitness)
				bestSpecimen = specimen;
		}
		return std::move(bestSpecimen);
	}

	GA::Specimen SingleSelection::get(GA::GeneticAlgorithm& ga)
	{
		return chain ? chain->get(ga) : ga.population[random.range(ga.population.size())];
	}

	GA::Specimen BestSelection::get(GA::GeneticAlgorithm& ga)
	{
		if (chain)
			return chain->get(ga);

		int best = 0;

		for (int i = 1; i < ga.population.size(); i++)
			if (ga.population[i].fitness < ga.population[best].fitness)
				best = i;

		return ga.population[best];
	}

	GA::Specimen BetterSelection::get(GA::GeneticAlgorithm& ga)
	{
		while (true)
		{
			GA::Specimen specimen = chain ? chain->get(ga) : ga.population[random.range(ga.population.size())];

			if (specimen.fitness <= ga.globalBest.fitness)
				return std::move(specimen);
		}
	}

	NewSelection::NewSelection(BMCP::Graph& graph)
	{
		baseGenotype.reserve(graph.slots);

		for (size_t i = 0; i < graph.nodes.size(); i++)
			for (size_t j = 0; j < graph.nodes[i].weight; j++)
				baseGenotype.push_back(i);
	}

	GA::Specimen NewSelection::get(GA::GeneticAlgorithm& ga)
	{
		GA::Specimen specimen;
		specimen.genotype = baseGenotype;

		std::random_shuffle(specimen.genotype.begin(), specimen.genotype.end());

		return specimen;
	}
}
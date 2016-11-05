// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Selection.h"

namespace BMCP_GA
{
	RingSelection::RingSelection(double ringSize) :
		ringSize(ringSize)
	{ }

	GA::Specimen RingSelection::get(GA::ComponentChain componentChain)
	{
		auto& population = componentChain.ga.population;

		GA::Specimen* bestSpecimen = &population[rand() % population.size()];

		for (int i = ringSize * population.size(); i >= 0; i--) 
		{
			GA::Specimen* specimen = &population[rand() % population.size()];

			if (specimen->fitness < bestSpecimen->fitness)
				bestSpecimen = specimen;
		}
		return *bestSpecimen;
	}

	RingMiddleSelection::RingMiddleSelection(int ringSize) :
		ringSize(ringSize)
	{ }

	GA::Specimen RingMiddleSelection::get(GA::ComponentChain componentChain)
	{
		GA::Specimen bestSpecimen = componentChain.get();

		for (int i = ringSize; i >= 0; i--)
		{
			GA::Specimen specimen = componentChain.get();

			if (specimen.fitness < bestSpecimen.fitness)
				bestSpecimen = std::move(specimen);
		}
		return std::move(bestSpecimen);
	}

	SingleSelection::SingleSelection()
	{ }

	GA::Specimen SingleSelection::get(GA::ComponentChain componentChain)
	{
		auto& population = componentChain.ga.population;

		return population[rand() % population.size()];
	}
}
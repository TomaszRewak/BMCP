// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Restore.h"
#include "GeneticAlgorithm\GeneticAlgorithm.h"

namespace BMCP_GA
{

	Restore::Restore(int afterGeneration) :
		afterGeneration(afterGeneration)
	{ }

	void Restore::prepare(GA::GeneticAlgorithm& geneticAlgorithm)
	{
		lastGeneration = 0;
	}

	GA::Specimen Restore::get(GA::ComponentChain componentChain)
	{
		auto specimen = componentChain.get();

		if (specimen.fitness <= componentChain.ga.globalBest.fitness)
			lastGeneration = componentChain.ga.currentGeneration();

		if (lastGeneration < componentChain.ga.currentGeneration() - afterGeneration)
		{
			lastGeneration = componentChain.ga.currentGeneration();
			return componentChain.ga.globalBest;
		}
		else
			return std::move(specimen);
	}
}
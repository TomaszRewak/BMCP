// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Restore.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"

namespace BMCP_GA
{

	Restore::Restore(int afterGeneration) :
		afterGeneration(afterGeneration)
	{ }

	GA::Specimen Restore::get(GA::GeneticAlgorithm& ga)
	{
		auto specimen = chain->get(ga);

		if (specimen.fitness <= ga.globalBest.fitness)
			lastGeneration = ga.currentGeneration();

		if (lastGeneration < ga.currentGeneration() - afterGeneration)
		{
			lastGeneration = ga.currentGeneration();
			return ga.globalBest;
		}
		else
			return std::move(specimen);
	}
}
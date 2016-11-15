// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <vector>

#include "Mutation.h"

namespace BMCP_GA
{
	Mutation::Mutation(double probability) :
		probability(probability)
	{ }

	GA::Specimen Mutation::get(GA::GeneticAlgorithm& ga)
	{
		GA::Specimen specimen = chain->get(ga);
		std::vector<int>& genotype = specimen.genotype;

		do {
			int a = rand() % genotype.size();
			int b = rand() % genotype.size();

			std::swap(genotype[a], genotype[b]);
		} while (random.uniform() <= probability);

		return std::move(genotype);
	}
}
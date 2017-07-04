// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <vector>
#include <algorithm>

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
			int a = genotype.size() * random.uniform();
			int b = genotype.size() * random.uniform();

			std::swap(genotype[a], genotype[b]);
		} while (random.uniform() <= probability);

		return std::move(genotype);
	}

	MutationMove::MutationMove(double probability) :
		probability(probability)
	{ }

	GA::Specimen MutationMove::get(GA::GeneticAlgorithm& ga)
	{
		GA::Specimen specimen = chain->get(ga);
		std::vector<int>& genotype = specimen.genotype;

		do {
			auto begin = genotype.begin() + genotype.size() * random.uniform();
			auto end = genotype.begin() + genotype.size() * random.uniform();

			if (begin > end) std::swap(begin, end);

			std::rotate(begin, begin + 1, end + 1);
		} while (random.uniform() <= probability);

		return std::move(genotype);
	}
}
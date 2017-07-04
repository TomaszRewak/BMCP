// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <climits>

#include "Specimen.h"

namespace GA
{
	Specimen::Specimen() :
		fitness(INT_MAX)
	{ }

	Specimen::Specimen(std::vector<int> genotype) :
		genotype(std::move(genotype)),
		fitness(INT_MAX)
	{ }
}
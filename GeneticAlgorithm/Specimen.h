// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <vector>

namespace GA
{
	class Specimen
	{
	public:
		int fitness;
		std::vector<int> genotype;

		Specimen();
		Specimen(std::vector<int> genotype);
	};
}
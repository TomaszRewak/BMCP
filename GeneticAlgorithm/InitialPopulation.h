// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Specimen.h"

#include <vector>

namespace GA
{
	class InitialPopulation
	{
	public:
		virtual std::vector<GA::Specimen> generate() = 0;
	};
}
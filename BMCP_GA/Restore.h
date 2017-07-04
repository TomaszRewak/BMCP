// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <random>

#include "../GeneticAlgorithm/Component.h"

namespace BMCP_GA
{
	class Restore : public GA::Component
	{
	private:
		int afterGeneration;
		int lastGeneration = 0;

	public:
		Restore(int afterGeneration);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
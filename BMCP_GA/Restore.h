// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <random>

#include "GeneticAlgorithm\Component.h"

namespace BMCP_GA
{
	class Restore : public GA::Component
	{
	private:
		int afterGeneration;
		int lastGeneration;

	public:
		Restore(int afterGeneration);

		virtual void prepare(GA::GeneticAlgorithm& geneticAlgorithm);
		virtual GA::Specimen get(GA::ComponentChain componentChain);
	};
}
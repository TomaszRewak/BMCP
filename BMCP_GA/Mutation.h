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
	class Mutation : public GA::Component
	{
	private:
		double probability;

		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;

	public:
		Mutation(double propability);

		virtual GA::Specimen get(GA::ComponentChain componentChain);
	};
}
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <random>

#include "GeneticAlgorithm\Component.h"
#include "BMCP\Graph.h"

namespace BMCP_GA
{
	class Crossing : public GA::Component
	{
	private:
		BMCP::Graph& graph;
		double probability;

		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;

	public:
		Crossing(BMCP::Graph& graph, double propability);

		virtual GA::Specimen get(GA::ComponentChain componentChain);
	};
}
// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Random.h"
#include "../GeneticAlgorithm/Component.h"
#include "../BMCP/Graph.h"

namespace BMCP_GA
{
	class Crossing : public GA::Component
	{
	private:
		BMCP::Graph& graph;
		double probability;

		Random random;

	public:
		Crossing(BMCP::Graph& graph, double propability);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
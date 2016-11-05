// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "BMCP\Greedy.h"
#include "Tabu\Tabu.h"
#include "GeneticAlgorithm\GeneticAlgorithm.h"

namespace BMCP_GA
{
	class Tabu : public GA::Component
	{
	public:
		TabuSearch::Tabu tabu;

	private:
		BMCP::Greedy greedy;
		int attempts;
		int slots;
		long long generation;

		int denialBandwidth;
		double targetDenial;

		int totalAttempts;
		int totalFailures;

	public:
		Tabu(int tabuSize, double targetDenial, int attempts, BMCP::Graph& graph);

		virtual void prepare(GA::GeneticAlgorithm& ga);
		virtual GA::Specimen get(GA::ComponentChain componentChain);
		virtual void log(GA::GeneticAlgorithm& ga);
	};
}
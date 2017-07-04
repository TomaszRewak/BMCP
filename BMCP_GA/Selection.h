// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Random.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"
#include "../GeneticAlgorithm/Component.h"
#include "../BMCP/Greedy.h"

namespace BMCP_GA
{
	class RingSelection : public GA::Component
	{
	private:
		int ringSize;

		Random random;

	public:
		RingSelection(int ringSize);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class SingleSelection : public GA::Component
	{
	private:
		Random random;

	public:
		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class BestSelection : public GA::Component
	{
	public:
		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class BetterSelection : public GA::Component
	{
	private:
		Random random;

	public:
		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class NewSelection : public GA::Component
	{
	private:
		std::vector<int> baseGenotype;

	public:
		NewSelection(BMCP::Graph& greedy);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
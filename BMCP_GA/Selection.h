// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "GeneticAlgorithm\GeneticAlgorithm.h"
#include "GeneticAlgorithm\Component.h"

namespace BMCP_GA
{
	class RingSelection : public GA::Component
	{
	private:
		double ringSize;

	public:
		RingSelection(double ringSize);

		virtual GA::Specimen get(GA::ComponentChain componentChain);
	};

	class RingMiddleSelection : public GA::Component
	{
	private:
		int ringSize;

	public:
		RingMiddleSelection(int ringSize);

		virtual GA::Specimen get(GA::ComponentChain componentChain);
	};

	class SingleSelection : public GA::Component
	{
	private:
		double ringSize;

	public:
		SingleSelection();

		virtual GA::Specimen get(GA::ComponentChain componentChain);
	};
}
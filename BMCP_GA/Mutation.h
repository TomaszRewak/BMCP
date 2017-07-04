// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Random.h"
#include "../GeneticAlgorithm/Component.h"

namespace BMCP_GA
{
	class Mutation : public GA::Component
	{
	private:
		double probability;
		Random random;

	public:
		Mutation(double propability);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class MutationMove : public GA::Component
	{
	private:
		double probability;
		Random random;

	public:
		MutationMove(double propability);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
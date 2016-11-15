#pragma once

#include "Random.h"
#include "GeneticAlgorithm\GeneticAlgorithm.h"

namespace BMCP_GA
{
	class SimulatesAnnealing : public GA::Component
	{
	private:
		double initialTemperature;
		double coolingRation;
		double baseShape;

		Random random;

	public:
		SimulatesAnnealing(double initialTemperature, double coolingRation, double baseShape);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
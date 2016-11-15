#pragma once

#include "SimulatedAnnealing.h"
#include <cmath>

namespace BMCP_GA
{
	SimulatedAnnealing::SimulatedAnnealing(double initialTemperature, double coolingRation, double baseShape) :
		initialTemperature(initialTemperature),
		coolingRation(coolingRation),
		baseShape(baseShape)
	{ }

	GA::Specimen SimulatedAnnealing::get(GA::GeneticAlgorithm& ga)
	{
		double temperature = initialTemperature * pow(baseShape, -(double)ga.currentGeneration() / coolingRation);

		for(int i = 0; i < 100; i++)
		{
			GA::Specimen specimen = chain->get(ga);

			double fvn = specimen.fitness;
			double fvc = ga.population[0].fitness;

			if (fvn <= fvc)
				return std::move(specimen);

			double threshold = exp((fvc - fvn) / temperature);
				
			if(random.uniform() < threshold)
				return std::move(specimen);
		}


		return chain->get(ga);
	}
}
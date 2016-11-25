#pragma once

#include <cmath>
#include <string>

#include "SimulatedAnnealing.h"

namespace BMCP_GA
{
	SimulatedAnnealing::SimulatedAnnealing(double initialTemperature, double coolingRation, double baseShape, int maxAttempts) :
		initialTemperature(initialTemperature),
		coolingRation(coolingRation),
		baseShape(baseShape),
		maxAttempts(maxAttempts)
	{ }

	GA::Specimen SimulatedAnnealing::get(GA::GeneticAlgorithm& ga)
	{
		double temperature = initialTemperature * pow(baseShape, -(double)ga.currentGeneration() / coolingRation);

		for (int i = 0; i < maxAttempts; i++)
		{
			GA::Specimen specimen = chain->get(ga);

			double fvn = specimen.fitness;
			double fvc = ga.population[0].fitness;

			if (fvn <= fvc)
				return std::move(specimen);

			double threshold = exp((fvc - fvn) / temperature);

			if (random.uniform() < threshold)
				return std::move(specimen);
		}


		return chain->get(ga);
	}

	TimedSimulatedAnnealing::TimedSimulatedAnnealing(double initialTemperature, double timeOf01) :
		initialTemperature(initialTemperature),
		timeOf01(timeOf01)
	{ }

	GA::Specimen TimedSimulatedAnnealing::get(GA::GeneticAlgorithm& ga)
	{
		double timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - ga.startTime).count() / 1000.;

		while (true)
		{
			GA::Specimen specimen = chain->get(ga);

			double fvn = specimen.fitness;
			double fvc = ga.population[0].fitness; // Sprawdziæ dla poprzedniego

			if (fvn <= fvc)
				return std::move(specimen);

			double threshold = exp(-2.30259 * (timeNow / timeOf01) * (fvn - fvc) / initialTemperature);

			if (random.uniform() < threshold)
				return std::move(specimen);
		}
	}

	TimedSimulatedAnnealingContext::TimedSimulatedAnnealingContext() :
		bestScore(INT_MAX)
	{ }

	TimedSimulatedAnnealingWithContext::TimedSimulatedAnnealingWithContext(TimedSimulatedAnnealingContext& context, double initialTemperature, double timeOf01) :
		context(context),
		initialTemperature(initialTemperature),
		timeOf01(timeOf01)
	{ }

	GA::Specimen TimedSimulatedAnnealingWithContext::get(GA::GeneticAlgorithm& ga)
	{
		double timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - ga.startTime).count() / 1000.;

		while (true)
		{
			GA::Specimen specimen = chain->get(ga);

			double fvn = specimen.fitness;
			double fvc = context.bestScore;

			if (fvn <= fvc) {
				context.bestScore = fvn;
				return std::move(specimen);
			}

			double threshold = exp(-2.30259 * (timeNow / timeOf01) * (fvn - fvc) / initialTemperature);

			if (random.uniform() < threshold) {
				context.bestScore = fvn;
				return std::move(specimen);
			}
		}
	}
}
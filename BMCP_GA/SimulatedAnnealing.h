#pragma once

#include "Random.h"
#include "GeneticAlgorithm\GeneticAlgorithm.h"

namespace BMCP_GA
{
	class SimulatedAnnealing : public GA::Component
	{
	private:
		double initialTemperature;
		double coolingRation;
		double baseShape;
		int maxAttempts;

		Random random;

	public:
		SimulatedAnnealing(double initialTemperature, double coolingRation, double baseShape, int maxAttempts = 100);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class TimedSimulatedAnnealing : public GA::Component
	{
	private:
		double initialTemperature;
		double timeOf01;

		Random random;

	public:
		TimedSimulatedAnnealing(double initialTemperature, double timeOf01);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class TimedSimulatedAnnealingContext
	{
	public:
		TimedSimulatedAnnealingContext();

		int bestScore;
	};

	class TimedSimulatedAnnealingWithContext : public GA::Component
	{
	private:
		TimedSimulatedAnnealingContext& context;

		double initialTemperature;
		double timeOf01;

		Random random;

	public:
		TimedSimulatedAnnealingWithContext(TimedSimulatedAnnealingContext& context, double initialTemperature, double timeOf01);

		virtual GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
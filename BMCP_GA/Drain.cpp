#include "Drain.h"

namespace BMCP_GA
{
	GA::Specimen NewPopulation::get(GA::GeneticAlgorithm& ga)
	{
		std::vector<GA::Specimen> newPopulation;
		newPopulation.reserve(ga.population.size());

		while (newPopulation.size() < ga.population.size())
			newPopulation.push_back(chain->get(ga));

		ga.population = std::move(newPopulation);

		return GA::Specimen();
	}

	GA::Specimen SamePopulation::get(GA::GeneticAlgorithm& ga)
	{
		for (int i = 0; i < ga.population.size(); i++)
			ga.population[i] = chain->get(ga);

		return GA::Specimen();
	}

	ResizedPopulation::ResizedPopulation(int newSize) :
		newSize(newSize)
	{ }

	GA::Specimen ResizedPopulation::get(GA::GeneticAlgorithm& ga)
	{
		std::vector<GA::Specimen> newPopulation;
		newPopulation.reserve(newSize);

		while (newPopulation.size() < newSize)
			newPopulation.push_back(chain->get(ga));

		ga.population = std::move(newPopulation);

		return GA::Specimen();
	}

	MapPopulation::MapPopulation(std::function<void(GA::ComponentChainBuilder&)> mappingFunction, int maxDiff) :
		mappingFunction(mappingFunction),
		maxDiff(maxDiff)
	{ }

	GA::Specimen MapPopulation::get(GA::GeneticAlgorithm& ga)
	{
		std::vector<GA::Specimen> newPopulation;
		newPopulation.reserve(ga.population.size());

		auto best = ga.globalBest;

		for (int i = 0; i < ga.population.size(); i++)
		{
			GA::Specimen specimen = ga.population[i];

			ga.globalBest = specimen;

			auto inlineComponent = std::make_shared<GA::InlineComponent>([&specimen](GA::GeneticAlgorithm& ga) {
				return specimen;
			});

			GA::ComponentChainBuilder builder(inlineComponent);
			mappingFunction(builder);

			auto newSpecimen = builder.chain->get(ga);

			if (newSpecimen.fitness - maxDiff > best.fitness)
				newSpecimen = best;

			newPopulation.push_back(std::move(newSpecimen));
		}

		ga.globalBest = best;

		ga.population = std::move(newPopulation);

		return GA::Specimen();
	}
}
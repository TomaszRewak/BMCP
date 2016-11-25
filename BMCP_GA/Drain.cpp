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
}
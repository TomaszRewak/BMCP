#pragma once

#include "../GeneticAlgorithm/Component.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"

namespace BMCP_GA
{
	class NewPopulation : public GA::Component
	{
		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class SamePopulation : public GA::Component
	{
		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class ResizedPopulation : public GA::Component
	{
	private:
		int newSize;

	public:
		ResizedPopulation(int newSize);

		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class MapPopulation : public GA::Component
	{
	private:
		int maxDiff;
		std::function<void(GA::ComponentChainBuilder&)> mappingFunction;

	public:
		MapPopulation(std::function<void(GA::ComponentChainBuilder&)> mappingFunction, int maxDiff);

		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
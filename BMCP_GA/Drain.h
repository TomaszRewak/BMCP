#pragma once

#include "GeneticAlgorithm/Component.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

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
}
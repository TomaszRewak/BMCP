#pragma once

#include <vector>

#include "../GeneticAlgorithm/GeneticAlgorithm.h"
#include "Random.h"

namespace BMCP_GA
{
	class Split : public GA::Component
	{
	private:
		std::vector<std::pair<int, std::shared_ptr<GA::Component>>> flows;

		int iteration = 0;
		int currentFlow = 0;

	public:
		Split(std::function<void(Split&)> generator);
		Split& with(int specimens, std::function<void(GA::ComponentChainBuilder&)> flow);

		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class Repeat : public GA::Component
	{
	private:
		int times;
		std::function<void(GA::ComponentChainBuilder&)> buildingFunction;

	public:
		Repeat(int times, std::function<void(GA::ComponentChainBuilder&)> buildingFunction);

		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class StoreAndForward : public GA::Component
	{
	private:
		std::function<void(GA::ComponentChainBuilder&)> buildingFunction;

	public:
		StoreAndForward(std::function<void(GA::ComponentChainBuilder&)> buildingFunction);

		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};

	class OneOf : public GA::Component
	{
	private:
		std::vector<std::function<void(GA::ComponentChainBuilder&)>> buildingFunctions;
		Random random;

	public:
		OneOf(std::vector<std::function<void(GA::ComponentChainBuilder&)>> buildingFunctions);

		GA::Specimen get(GA::GeneticAlgorithm& ga) override;
	};
}
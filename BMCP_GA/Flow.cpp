#pragma once

#include "Flow.h"

namespace BMCP_GA
{
	Split::Split(std::function<void(Split&)> generator)
	{
		generator(*this);
	}

	Split& Split::with(int specimens, std::function<void(GA::ComponentChainBuilder&)> flow)
	{
		GA::ComponentChainBuilder builder(chain);
		flow(builder);

		flows.push_back(std::make_pair(specimens, builder.chain));

		return *this;
	}

	GA::Specimen Split::get(GA::GeneticAlgorithm& ga)
	{
		if (iteration >= flows[currentFlow].first)
		{
			iteration = 0;
			currentFlow++;

			if (currentFlow >= flows.size())
				currentFlow = 0;
		}

		iteration++;

		return flows[currentFlow].second->get(ga);
	}

	Repeat::Repeat(int times, std::function<void(GA::ComponentChainBuilder&)> buildingFunction) :
		times(times),
		buildingFunction(buildingFunction)
	{ }

	GA::Specimen Repeat::get(GA::GeneticAlgorithm& ga)
	{
		int iterations = times;

		std::shared_ptr<GA::Component> repeatedChain = nullptr;
		std::shared_ptr<GA::Component> finalChain = this->chain;

		auto inlineComponent = std::make_shared<GA::InlineComponent>([&iterations, &repeatedChain, &finalChain](GA::GeneticAlgorithm& ga) {
			if (iterations-- > 0)
				return repeatedChain->get(ga);
			else
				return finalChain->get(ga);
		});

		GA::ComponentChainBuilder builder(inlineComponent);
		buildingFunction(builder);
		repeatedChain = builder.chain;

		return inlineComponent->get(ga);
	}

	StoreAndForward::StoreAndForward(std::function<void(GA::ComponentChainBuilder&)> buildingFunction) :
		buildingFunction(buildingFunction)
	{ }

	GA::Specimen StoreAndForward::get(GA::GeneticAlgorithm& ga)
	{
		GA::Specimen specimen = chain->get(ga);

		auto inlineComponent = std::make_shared<GA::InlineComponent>([&specimen](GA::GeneticAlgorithm& ga) {
			return specimen;
		});

		GA::ComponentChainBuilder builder(inlineComponent);
		buildingFunction(builder);

		return builder.chain->get(ga);
	}
}
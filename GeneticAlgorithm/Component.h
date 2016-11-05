// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Specimen.h"

#include <vector>
#include <memory>

namespace GA
{
	class GeneticAlgorithm;
	class Component;

	class ComponentChain
	{
	private:
		std::vector<std::shared_ptr<Component>>::reverse_iterator current;
		std::vector<std::shared_ptr<Component>>::reverse_iterator last;

	public:
		GeneticAlgorithm &ga;

		ComponentChain(
			GeneticAlgorithm& ga,
			std::vector<std::shared_ptr<Component>>::reverse_iterator current,
			std::vector<std::shared_ptr<Component>>::reverse_iterator last);

		Specimen get();
		ComponentChain skip(int by);
	};

	class Component
	{
	public:
		virtual void reset(GA::GeneticAlgorithm& ga);
		virtual void prepare(GA::GeneticAlgorithm& ga);
		virtual Specimen get(ComponentChain componentChain) = 0;
		virtual void log(GeneticAlgorithm& ga);
	};
}
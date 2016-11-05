// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Component.h"

namespace GA
{
	ComponentChain::ComponentChain(
		GeneticAlgorithm& ga,
		std::vector<std::shared_ptr<Component>>::reverse_iterator current,
		std::vector<std::shared_ptr<Component>>::reverse_iterator last)
		:
		ga(ga),
		current(current),
		last(last)
	{ }

	Specimen ComponentChain::get()
	{
		ComponentChain newChain = *this;
		newChain.current++;

		if (current == last)
			throw "End of pipeline";

		return (*current)->get(newChain);
	}

	ComponentChain ComponentChain::skip(int by)
	{
		ComponentChain newChain = *this;
		newChain.current += by;
		return newChain;
	}

	void Component::reset(GA::GeneticAlgorithm& ga)
	{ }

	void Component::prepare(GA::GeneticAlgorithm& ga)
	{ }

	void Component::log(GeneticAlgorithm& ga)
	{ }
}
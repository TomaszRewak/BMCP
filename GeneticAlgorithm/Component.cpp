// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Component.h"

namespace GA
{
	ComponentChainBuilder::ComponentChainBuilder(std::shared_ptr<Component> chain) :
		chain(chain)
	{ }

	ComponentChainBuilder& ComponentChainBuilder::with(std::shared_ptr<Component> component)
	{
		component->chain = chain;
		chain = component;

		return *this;
	}

	InlineComponent::InlineComponent(std::function<Specimen(GeneticAlgorithm& ga)> inlineFunction):
		inlineFunction(inlineFunction)
	{ }


	Specimen InlineComponent::get(GeneticAlgorithm& ga)
	{
		return inlineFunction(ga);
	}
}
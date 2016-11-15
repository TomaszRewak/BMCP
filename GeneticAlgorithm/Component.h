// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Specimen.h"

#include <vector>
#include <memory>
#include <functional>

namespace GA
{
	class GeneticAlgorithm;
	class Component;

	class Component
	{
	public:
		std::shared_ptr<Component> chain;

		virtual Specimen get(GeneticAlgorithm& ga) = 0;
	};

	class ComponentChainBuilder
	{
	private:
		ComponentChainBuilder& with(std::shared_ptr<Component> component);

	public:
		std::shared_ptr<Component> chain;
		ComponentChainBuilder(std::shared_ptr<Component> chain = nullptr);

		template<typename T, typename... Args>
		ComponentChainBuilder& with(Args&&... args) { return with(std::make_shared<T>(std::forward<Args>(args)...)); }
	};

	class InlineComponent : public Component
	{
	private:
		std::function<Specimen(GeneticAlgorithm& ga)> inlineFunction;

	public:
		InlineComponent(std::function<Specimen(GeneticAlgorithm& ga)> inlineFunction);

		virtual Specimen get(GeneticAlgorithm& ga) override;
	};
}
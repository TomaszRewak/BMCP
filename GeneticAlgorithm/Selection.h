// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <memory>

#include "Specimen.h"

namespace GA
{
	class SelectionGenerator
	{
	protected:
		std::vector<Specimen>& population;

	public:
		SelectionGenerator(std::vector<Specimen>& population);

		virtual Specimen& getNext() = 0;
	};

	class Selection
	{
	public:
		virtual std::unique_ptr<SelectionGenerator> getGenerator(std::vector<Specimen>& population) = 0;
	};
}
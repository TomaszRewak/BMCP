// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include <vector>
#include <algorithm>
#include <ostream>

#include "Graph.h"

namespace BMCP
{
	class Coloring {
	public:
		std::vector<std::vector<int>> genotype;
		int colors = 0;

		size_t size();

		Coloring(Graph& graph);

		void sortNode(int i);
		void sort();
	};

	std::ostream& operator<<(std::ostream& stream, Coloring& specimen);
}
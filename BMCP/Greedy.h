// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#pragma once

#include "Coloring.h"
#include "Graph.h"

#include <vector>
#include <algorithm>

namespace BMCP
{
	class Greedy {
	protected:
		struct RangeEnd {
			int count = 0;
			int supportedBy = 0;
		};

		struct GreedyNode {
			std::vector<RangeEnd> ranges;
			int totalStep = 0;
			int	done = 0;
			int color = 0;
			int size = 0;

			GreedyNode();

			int nextColor();
			void addRangeEnd(int position, bool begin);
			void reset();
		};

		std::vector<GreedyNode> nodes;

		void reset();

	public:
		Graph &graph;

		Greedy(Graph &g);

		int rate(std::vector<int>& specimen);
		Coloring findColoring(std::vector<int>& specimen);

		bool test(Coloring& coloring);
	};
}
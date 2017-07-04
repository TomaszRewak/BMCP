// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Greedy.h"

#include <cstring>

namespace BMCP
{
	Greedy::GreedyNode::GreedyNode() :
		ranges(1000)
	{
		reset();
	}

	int Greedy::GreedyNode::nextColor() {
		while (totalStep != 0) {
			color++;
			totalStep += ranges[color];
		}

		return color;
	}

	void Greedy::GreedyNode::addRangeEnd(int position, bool begin) {
		int step = begin ? 1 : -1;

		if (position <= color) {
			totalStep += step;
		}
		else {
			if (position >= ranges.size())
				ranges.resize(position + 200);

			ranges[position] += step;

			size = std::max(size, position + 1);
		}
	}

	void Greedy::GreedyNode::reset() {
		std::memset(&ranges[0], 0, size * sizeof ranges[0]);

		totalStep = 0;
		done = 0;
		color = 0;
		size = 0;
	}

	void Greedy::reset() {
		for (auto&& node : nodes)
			node.reset();
	}

	Greedy::Greedy(Graph &g) :
		graph(g),
		nodes(g.nodes.size())
	{ }

	int Greedy::rate(std::vector<int>& specimen) {
		reset();

		int totalColors = -1;

		for (auto nodeIndex : specimen)
		{
			GreedyNode &node = nodes[nodeIndex];

			int color = node.nextColor();

			totalColors = std::max(totalColors, color);

			for (auto&& neighbour : graph.neighbours[nodeIndex])
			{
				nodes[neighbour.node].addRangeEnd(color - neighbour.weight + 1, true);
				nodes[neighbour.node].addRangeEnd(color + neighbour.weight, false);
			}

			node.done++;
		}

		return totalColors + 1;
	}

	Coloring Greedy::findColoring(std::vector<int>& specimen) {
		reset();

		Coloring coloring(graph);

		for (auto nodeIndex : specimen)
		{
			GreedyNode &node = nodes[nodeIndex];

			int color = node.nextColor();

			coloring.colors = std::max(coloring.colors, color + 1);
			coloring.genotype[nodeIndex][node.done] = color;

			for (auto&& neighbour : graph.neighbours[nodeIndex])
			{
				nodes[neighbour.node].addRangeEnd(color - neighbour.weight + 1, true);
				nodes[neighbour.node].addRangeEnd(color + neighbour.weight, false);
			}

			node.done++;
		}

		return std::move(coloring);
	}

	bool Greedy::test(Coloring& coloring)
	{
		auto& colors = coloring.genotype;

		if (graph.nodes.size() != colors.size())
			return false;

		for (int i = 0; i < graph.nodes.size(); i++)
			if (colors[i].size() != graph.nodes[i].weight)
				return false;

		for (auto& edge : graph.edges)
			for (int i = 0; i < colors[edge.nodeA].size(); i++)
				for (int j = 0; j < colors[edge.nodeB].size(); j++)
					if (i != j || edge.nodeA != edge.nodeB)
						if (std::abs(colors[edge.nodeA][i] - colors[edge.nodeB][j]) < edge.weight)
							return false;

		return true;
	}
}
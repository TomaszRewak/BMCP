// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "Coloring.h"

namespace BMCP
{
	size_t Coloring::size()
	{
		return genotype.size();
	}

	Coloring::Coloring(Graph& graph)
	{
		genotype.resize(graph.nodes.size());

		for (size_t i = 0; i < graph.nodes.size(); i++)
			genotype[i] = std::vector<int>(graph.nodes[i].weight, 0);
	}

	void Coloring::sortNode(int i)
	{
		std::sort(genotype[i].begin(), genotype[i].end());
	}

	void Coloring::sort()
	{
		for (int i = 0; i < genotype.size(); i++)
			sortNode(i);
	}

	std::ostream& operator<<(std::ostream& stream, Coloring& specimen) {
		for (int i = 0; i < specimen.size(); i++) {
			stream << (i + 1);
			for (int g : specimen.genotype[i])
				stream << " " << g;
			stream << std::endl;
		}

		return stream;
	}
}
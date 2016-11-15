// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <vector>

#include "Crossing.h"

namespace BMCP_GA
{
	Crossing::Crossing(BMCP::Graph& graph, double probability) :
		graph(graph),
		probability(probability)
	{ }

	GA::Specimen Crossing::get(GA::GeneticAlgorithm& ga)
	{
		if (random.uniform() <= probability)
		{
			int size = graph.slots;

			GA::Specimen specimenA = chain->get(ga);
			GA::Specimen specimenB = chain->get(ga);

			std::vector<int>& genotypeA = specimenA.genotype;
			std::vector<int>& genotypeB = specimenB.genotype;

			int crossPoint = rand() % size;
			std::vector<int> nodesCount(size, 0);

			for (int i = 0; i < crossPoint; i++)
				nodesCount[genotypeA[i]]++;

			for (int i = size - 1, j = size - 1; i >= 0 && j >= crossPoint; i--)
			{
				int node = genotypeB[i];
				if (nodesCount[node] < graph.nodes[node].weight)
				{
					genotypeA[j] = node;
					nodesCount[node]++;
					j--;
				}
			}

			return std::move(genotypeA);
		}
		else
			return std::move(chain->get(ga));
	}
}
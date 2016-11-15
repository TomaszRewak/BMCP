// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include <string>

#include "Tabu.h"

namespace BMCP_GA
{
	Tabu::Tabu(int tabuSize, double targetDenial, int attempts, BMCP::Graph& graph) :
		targetDenial(targetDenial),
		attempts(attempts),
		greedy(BMCP::Greedy(graph)),
		tabu(TabuSearch::Tabu(tabuSize, 16)),
		generation(0),
		denialBandwidth(100)
	{
		slots = graph.slots;
	}

	GA::Specimen Tabu::get(GA::GeneticAlgorithm& ga)
	{
		generation++;

		if (totalAttempts > denialBandwidth)
		{
			if (((double)totalFailures / (double)totalAttempts) > targetDenial)
				tabu.maxDiff = tabu.maxDiff * 0.7;
			else
				tabu.maxDiff += std::max(1., tabu.maxDiff * 0.3);

			totalFailures = totalFailures * denialBandwidth / totalAttempts * 0.3;
			totalAttempts = denialBandwidth * 0.3;
		}

		totalAttempts++;

		for (int i = 0; i < attempts; i++)
		{
			GA::Specimen specimen = chain->get(ga);
			std::vector<int>& genotype = specimen.genotype;

			auto coloring = greedy.findColoring(genotype);
			specimen.fitness = coloring.colors;

			std::vector<int> fingerprint;
			fingerprint.reserve(slots + 1);
			fingerprint.push_back(coloring.colors * 100);

			for (auto& row : coloring.genotype)
				for (auto color : row)
					fingerprint.push_back(color);

			if (tabu.isUnique(fingerprint))
			{
				tabu.insert(fingerprint, generation);
				return std::move(specimen);
			}

			totalFailures++;
		}

		GA::Specimen specimen = chain->get(ga);
		specimen.fitness = greedy.rate(specimen.genotype);
		return std::move(specimen);
	}
}
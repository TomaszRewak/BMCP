// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "BMCP_GA\InitialPopulation.h"
#include "BMCP_GA\Mutation.h"
#include "BMCP_GA\Crossing.h"
#include "BMCP_GA\Fitness.h"
#include "BMCP_GA\Selection.h"
#include "BMCP_GA\Tabu.h"
#include "BMCP_GA\StopCondition.h"
#include "BMCP_GA\Restore.h"
#include "BMCP_GA\Drain.h"
#include "BMCP_GA\Flow.h"
#include "BMCP_GA\SimulatedAnnealing.h"
#include "FitnessLog.hpp"

#include <iostream>
#include <fstream>

int main()
{
	std::srand(std::time(0));

	std::string graphs[] = {
		/*"GEOM40",
		"GEOM40a",
		"GEOM40b",*/

		"GEOM60",
		"GEOM60a",
		"GEOM60b",

		"GEOM70",
		"GEOM70a",
		"GEOM70b",

		/*"GEOM80",
		"GEOM80a",
		"GEOM80b",

		"GEOM90",
		"GEOM90a",
		"GEOM90b",

		"GEOM100",
		"GEOM100a",
		"GEOM100b",

		"GEOM120",
		"GEOM120a",
		"GEOM120b",*/
	};

	for (int iteration = 0; iteration < 1; iteration++)
		for (auto graphName : graphs)
		{
			std::string testCase = graphName + " " + std::to_string(iteration);
			std::cout << testCase << std::endl;

			std::ifstream input;
			input.open("IN/" + graphName + ".col");

			BMCP::Graph graph;
			input >> graph;
			input.close();

			GA::GeneticAlgorithm ga;
			FitnessLogScope logScope;

			ga
				.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 1)
				.withStopCondition<BMCP_GA::TimeStopCondition>(300)
				.with([&](GA::ComponentChainBuilder& builder) { builder
					.with<BMCP_GA::SingleSelection>()
					.with<BMCP_GA::Mutation>(0.2)
					.with<BMCP_GA::Fitness>(graph)
					.with<BMCP_GA::RingSelection>(10)
					.with<BMCP_GA::SimulatedAnnealing>(10., 1000., 1.2)
					.with<BMCP_GA::NewPopulation>()
					.with<FitnessLog>(logScope); });

			ga.start();

			BMCP::Greedy greedy = BMCP::Greedy(graph);
			auto coloring = greedy.findColoring(ga.globalBest.genotype);

			{
				std::ofstream output;
				if (greedy.test(coloring))
					output.open("Out/" + graphName + " " + std::to_string(coloring.colors) + ".color");
				output << coloring;
				output.close();
			}

			{
				std::ofstream output;
				output.open("Out/fitness_global " + testCase + " " + std::to_string(coloring.colors) + ".out");
				for (auto line : ga.logs["fitness_global"])
					output << line << std::endl;
				output.close();
			}
		}
}
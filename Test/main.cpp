// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "GeneticAlgorithm/Builder.h"
#include "BMCP_GA\InitialPopulation.h"
#include "BMCP_GA\Mutation.h"
#include "BMCP_GA\Crossing.h"
#include "BMCP_GA\Fitness.h"
#include "BMCP_GA\Selection.h"
#include "BMCP_GA\Tabu.h"
#include "BMCP_GA\StopCondition.h"
#include "BMCP_GA\Restore.h"
#include "FitnessLog.hpp"

#include <iostream>
#include <fstream>

int main()
{
	std::srand(std::time(0));

	std::string graphs[] = {
		"GEOM120",
		"GEOM120a",
		"GEOM120b",

		"GEOM100",
		"GEOM100a",
		"GEOM100b",

		"GEOM90",
		"GEOM90a",
		"GEOM90b",

		"GEOM80",
		"GEOM80a",
		"GEOM80b",

		"GEOM70",
		"GEOM70a",
		"GEOM70b",

		"GEOM60",
		"GEOM60a",
		"GEOM60b",

		"GEOM40",
		"GEOM40a",
		"GEOM40b",
	};

	for (int iteration = 0; iteration < 10; iteration++)
		for (auto graphName : graphs)
		{
			std::string testCase = graphName + " " + std::to_string(iteration);
			std::cout << testCase << std::endl;

			std::ifstream input;
			input.open("IN/" + graphName + ".col");

			BMCP::Graph graph;
			input >> graph;
			input.close();

			auto ga = GA::Builder::std()
				.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 100)
				.withStopCondition<BMCP_GA::TimeStopCondition>(2000)
				.with<BMCP_GA::RingSelection>(0.1)
				//.with<BMCP_GA::SingleSelection>()
				.with<BMCP_GA::Mutation>(0.2)
				//.with<BMCP_GA::Crossing>(graph, 0.2)
				.with<BMCP_GA::Fitness>(graph)
				//.with<BMCP_GA::Tabu>(20000000, tabu, 10, graph)
				.with<BMCP_GA::RingMiddleSelection>(10)
				.with<BMCP_GA::Restore>(100)
				.with<FitnessLog>();
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
				output.open("Out/fitness " + testCase + " " + std::to_string(coloring.colors) + ".out");
				for (auto line : ga.logs["fitness_global"])
					output << line << std::endl;
				output.close();
			}
		}
}
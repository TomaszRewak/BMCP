// ========================================
// ======= Created by Tomasz Rewak ========
// ========================================
// ==== https://github.com/TomaszRewak ====
// ========================================

#include "../BMCP_GA/InitialPopulation.h"
#include "../BMCP_GA/Mutation.h"
#include "../BMCP_GA/Crossing.h"
#include "../BMCP_GA/Fitness.h"
#include "../BMCP_GA/Selection.h"
#include "../BMCP_GA/Tabu.h"
#include "../BMCP_GA/StopCondition.h"
#include "../BMCP_GA/Restore.h"
#include "../BMCP_GA/Drain.h"
#include "../BMCP_GA/Flow.h"
#include "../BMCP_GA/SimulatedAnnealing.h"
#include "FitnessLog.hpp"

#include <climits>
#include <iostream>
#include <fstream>

struct testAlgorithm {
	virtual void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph) = 0;
};

struct greedyAlgorithm : public testAlgorithm {
	void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph)
	{
		FitnessLogScope logScope;

		ga
			.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 1)
			.with([&](GA::ComponentChainBuilder& builder) { builder
				.with<BMCP_GA::NewSelection>(graph)
				.with<BMCP_GA::Fitness>(graph)
				.with<BMCP_GA::NewPopulation>()
				.with<FitnessLog>(graph, logScope); });

		ga.start();
	}
};

struct gaAlgorithm : public testAlgorithm {
	void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph)
	{
		FitnessLogScope logScope;
		BMCP_GA::TimedSimulatedAnnealingContext annealingContext;

		ga
			.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 1000)
			.with([&](GA::ComponentChainBuilder& builder) { builder
				.with<BMCP_GA::RingSelection>(10)
				.with<BMCP_GA::Mutation>(0.2)
				.with<BMCP_GA::Fitness>(graph)
				.with<BMCP_GA::NewPopulation>()
				.with<FitnessLog>(graph, logScope); });

		ga.start();
	}
};

struct lsAlgorithm : public testAlgorithm {
	void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph)
	{
		FitnessLogScope logScope;
		BMCP_GA::TimedSimulatedAnnealingContext annealingContext;

		ga
			.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 1)
			.with([&](GA::ComponentChainBuilder& builder) { builder
				.with<BMCP_GA::SingleSelection>()
				.with<BMCP_GA::Mutation>(0.2)
				.with<BMCP_GA::Fitness>(graph)
				.with<BMCP_GA::RingSelection>(100)
				.with<BMCP_GA::NewPopulation>()
				.with<FitnessLog>(graph, logScope); });

		ga.start();
	}
};

struct saAlgorithm : public testAlgorithm {
	int time;
	saAlgorithm(int time) : time(time) { }

	void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph)
	{
		FitnessLogScope logScope;
		BMCP_GA::TimedSimulatedAnnealingContext annealingContext;

		ga
			.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 1000)
			.with([&](GA::ComponentChainBuilder& builder) { builder
				.with<BMCP_GA::BestSelection>()
				.with<BMCP_GA::Mutation>(0.2)
				.with<BMCP_GA::Fitness>(graph)
				.with<BMCP_GA::TimedSimulatedAnnealingWithContext>(annealingContext, time)
				.with<BMCP_GA::ResizedPopulation>(1)
				.with<FitnessLog>(graph, logScope); });

		ga.start();
	}
};

struct lsxAlgorithm : public testAlgorithm {
	void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph)
	{
		FitnessLogScope logScope;
		BMCP_GA::TimedSimulatedAnnealingContext annealingContext;

		ga
			.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 1)
			.with([&](GA::ComponentChainBuilder& builder) { builder
				.with<BMCP_GA::SingleSelection>()
				.with<BMCP_GA::Mutation>(0.2)
				.with<BMCP_GA::Fitness>(graph)
				.with<BMCP_GA::BetterSelection>()
				.with<BMCP_GA::NewPopulation>()
				.with<FitnessLog>(graph, logScope); });

		ga.start();
	}
};

struct newAlgorithm : public testAlgorithm {
	newAlgorithm() { }

	void run(GA::GeneticAlgorithm& ga, BMCP::Graph& graph)
	{
		FitnessLogScope logScope;
		BMCP_GA::TimedSimulatedAnnealingContext annealingContext;

		ga
			.withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 10)
			.with([&](GA::ComponentChainBuilder& builder) { builder
				.with<BMCP_GA::MapPopulation>([&](GA::ComponentChainBuilder& builder) {
			builder
				.with<BMCP_GA::Mutation>(0.2)
				.with<BMCP_GA::Fitness>(graph)
				.with<BMCP_GA::BetterSelection>();
		},
					0)
				.with<FitnessLog>(graph, logScope); });

		ga.start();
	}
};

struct testCase {
	testCase(int time, int dataSet, std::shared_ptr<testAlgorithm> alg) : time(time), dataSet(dataSet), alg(alg) { }

	int time;
	int dataSet;
	std::shared_ptr<testAlgorithm> alg;
};

int main(int argc, char* argv[])
{
	std::srand(std::time(0));

	std::vector<std::string> dataSets[]{
		std::vector<std::string> {"20", "20a", "20b", "30", "30a", "30b", "40", "40a", "40b", "50", "50a", "50b", "60", "60a", "60b", "70", "70a", "70b", "80", "80a", "80b", "90", "90a", "90b", "100", "100a", "100b", "110", "110a", "110b", "120", "120a", "120b"},
		std::vector<std::string> {"20_BCP", "20a_BCP", "20b_BCP", "30_BCP", "30a_BCP", "30b_BCP", "40_BCP", "40a_BCP", "40b_BCP", "50_BCP", "50a_BCP", "50b_BCP", "60_BCP", "60a_BCP", "60b_BCP", "70_BCP", "70a_BCP", "70b_BCP", "80_BCP", "80a_BCP", "80b_BCP", "90_BCP", "90a_BCP", "90b_BCP", "100_BCP", "100a_BCP", "100b_BCP", "110_BCP", "110a_BCP", "110b_BCP", "120_BCP", "120a_BCP", "120b_BCP"},
		std::vector<std::string> {"60", "60a", "60b", "120", "120a", "120b"},
		std::vector<std::string> {"90a"},
	};

	testCase testCases[]{
		testCase(300, 0, std::make_shared<greedyAlgorithm>()), // 0
		testCase(300, 0, std::make_shared<gaAlgorithm>()), // 1
		testCase(300, 0, std::make_shared<lsAlgorithm>()), // 2
		testCase(300, 0, std::make_shared<lsxAlgorithm>()), // 3
		testCase(300, 0, std::make_shared<saAlgorithm>(15)), // 4
		testCase(2000, 2, std::make_shared<lsxAlgorithm>()), // 5
		testCase(2000, 2, std::make_shared<saAlgorithm>(100)), // 6

		testCase(2000, 3, std::make_shared<lsxAlgorithm>()), // 7
		testCase(2000, 3, std::make_shared<newAlgorithm>()), // 8
		testCase(2000, 3, std::make_shared<newAlgorithm>()), // 9
	};

	if (argc < 2) 
	{
		std::cout << "Test number not provided" << std::endl;
		return 1;
	}

	int testNumber = std::stoi(argv[1]);
	testCase test = testCases[testNumber];

	for (int iteration = 0; iteration < 10; iteration++)
		for (auto graphName : dataSets[test.dataSet])
		{

			std::string testName = std::to_string(testNumber) + " " + graphName;
			std::string testCase = testName + " " + std::to_string(iteration);
			std::cout << testCase << std::endl;

			std::ifstream input;
			input.open("In/GEOM" + graphName + ".col");

			BMCP::Graph graph;
			input >> graph;
			input.close();

			GA::GeneticAlgorithm ga;
			ga.withStopCondition<BMCP_GA::TimeStopCondition>(test.time);

			test.alg->run(ga, graph);

			BMCP::Greedy greedy = BMCP::Greedy(graph);
			auto coloring = greedy.findColoring(ga.globalBest.genotype);

			{
				std::ofstream output;
				if (greedy.test(coloring))
					output.open("Out/coloring " + graphName + " " + std::to_string(coloring.colors) + ".color");
				output << coloring;
				output.close();
			}

			{
				std::ofstream output;
				output.open("Out/fitness " + testName + " all.out", std::fstream::out | std::fstream::app);
				for (auto line : ga.logs["fitness_global"])
					output << line << std::endl;
				output.close();
			}
		}
}
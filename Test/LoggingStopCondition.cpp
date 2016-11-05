#include <algorithm>

#include "BMCP_GA\StopCondition.h"
#include "LoggingStopCondition.h"

LoggingStopCondition::LoggingStopCondition(std::ostream& stream, int generations) :
	BMCP_GA::StopCondition(generations),
	stream(stream)
{ }

bool LoggingStopCondition::checkCondition(GA::GeneticAlgorithm& geneticAlgorithm)
{
	int min = INT_MAX,
		max = INT_MIN,
		avg = 0;

	for (auto& specimen : geneticAlgorithm.population)
	{
		min = std::min(min, specimen.fitness);
		max = std::max(min, specimen.fitness);
		avg += specimen.fitness;
	}

	avg /= geneticAlgorithm.population.size();

	stream << geneticAlgorithm.currentGeneration() << "\t" << min << "\t" << avg << "\t" << max << std::endl;

	return BMCP_GA::StopCondition::checkCondition(geneticAlgorithm);
}
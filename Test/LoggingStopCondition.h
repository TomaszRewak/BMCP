#pragma once

#include "BMCP_GA\StopCondition.h"

#include <ostream>

class LoggingStopCondition : public BMCP_GA::StopCondition
{
private:
	std::ostream& stream;

public:
	LoggingStopCondition(std::ostream& stream, int generations);

	virtual bool checkCondition(GA::GeneticAlgorithm& geneticAlgorithm);
};
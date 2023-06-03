#include <random>
#include <chrono>

#include "functions.h"

double random(const int& range)
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::normal_distribution<double> rozklad(0, range);
	return rozklad(engine);
}
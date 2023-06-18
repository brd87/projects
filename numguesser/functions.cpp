#include <random>
#include <chrono>

#include "functions.h"

double random(const int& range)
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> rozklad(0, range);
	return rozklad(engine);
}
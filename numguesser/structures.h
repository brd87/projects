#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>

struct MINSTdata
{
	int label;
	std::vector<double> pixels;
	double targetOutput[10] = { 0 };
};

#endif
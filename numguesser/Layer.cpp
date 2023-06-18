#include <vector>

#include "classes.h"

void Layer::modify_Neurons(const int& index, const std::vector<double>& newNeurons)
{
	neurons[index] = newNeurons;
}
void Layer::add_Neurons(const std::vector<double>& newNeurons)
{
	neurons.push_back(newNeurons);
}
std::vector<double> Layer::return_Neurons(const int& index)
{
	return neurons[index];
}
std::vector<std::vector<double>> Layer::return_allNeurons()
{
	return neurons;
}
void Layer::kill_neurons()
{
	neurons.clear();
}
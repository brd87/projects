#include <vector>
#include <iostream> //temp<<<<<<

#include "classes.h"

/*
double Layer::sigmoid(const double& neuron)
{
	return 1 / (1 + exp(neuron));
}
double Layer::sigmoidDerivative(const double& neuron)
{
	return sigmoid(neuron) * (1 - sigmoid(neuron));
}
*/

/*
void Layer::derNeurons()
{
	for (auto i : neurons)
	{
		derivedNeurons.push_back(sigmoidDerivative(i));
	}
}
*/
////modify&return
/*
void Layer::modify_Neurons(const std::vector<double>& newNeurons)
{
	neurons.clear();
	neurons = newNeurons;
}
std::vector<double> Layer::return_Neurons()
{
	return neurons;
}
*/
void Layer::modify_Neurons(const int& index, const std::vector<double>& newNeurons)
{
	neurons[index] = newNeurons;
}
void Layer::add_Neurons(const std::vector<double>& newNeurons)
{
	//std::cout << "added";//temp<<<<<<
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
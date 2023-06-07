#include <vector>
#include <iostream>//temp<<<<<<

#include "classes.h"


std::vector<double> Processing::calculateActivation(const std::vector<double>& inputNeurons, const std::vector<std::vector<double>>& weights, const std::vector<double>& bias)
{
	std::cout << "ACT";//temp<<<<<<
	std::vector<double> outputNeurons;
	for (int i = 0; i < bias.size(); i++)
	{
		outputNeurons.push_back(sigmoid(singleWABprocessing(inputNeurons, weights[i], bias[i])));
		//std::cout << "333";//temp<<<<<<
	}
	std::cout << "done";//temp<<<<<<
	return outputNeurons;
}
double Processing::singleWABprocessing(const std::vector<double>& inputNeurons, const std::vector<double>& inputWeights, const double& inputbias)
{
	//std::cout << "inputNeurons size: " << inputNeurons.size() << std::endl;//temp<<<<<<
	//std::cout << "inputWeights size: " << inputWeights.size() << std::endl;//temp<<<<<<
	//std::cout << "000";//temp<<<<<<
	
	double holdNeuron = 0;
	for (int i = 0; i < inputWeights.size(); i++) holdNeuron += inputWeights[i] * inputNeurons[i];
	//for (int i = 0; i < 784; i++) holdNeuron += inputWeights[i] * inputNeurons[i];
	//std::cout << "111";//temp<<<<<<
	return holdNeuron + inputbias;
}
double Processing::sigmoid(const double& neuron)
{
	//std::cout << "222";//temp<<<<<<
	return 1 / (1 + exp(neuron));
}
double Processing::sigmoidDerivative(const double& neuron)
{
	return sigmoid(neuron) * (1 - sigmoid(neuron));
}

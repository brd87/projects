#include <vector>

#include "classes.h"


std::vector<double> Processing::calculateActivation(const std::vector<double>& inputNeurons, const std::vector<std::vector<double>>& weights, const std::vector<double>& bias)
{
	std::vector<double> outputNeurons;
	for (int i = 0; i < bias.size(); i++)
	{
		outputNeurons.push_back(sigmoid(singleWABprocessing(inputNeurons, weights[i], bias[i])));
	}
	return outputNeurons;
}
double Processing::singleWABprocessing(const std::vector<double>& inputNeurons, const std::vector<double>& inputWeights, const double& inputbias)
{
	double holdNeuron = 0;
	for (int i = 0; i < inputWeights.size(); i++) holdNeuron += inputWeights[i] * inputNeurons[i];
	return holdNeuron + inputbias;
}

double Processing::sigmoid(const double& neuron)
{
	return 1 / (1 + exp(neuron));
}
double Processing::sigmoidDerivative(const double& neuron)
{
	return neuron * (1 - neuron);
}

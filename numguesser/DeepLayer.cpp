#include <random>
#include <chrono>
#include <iostream>//temp<<<<<<

#include "classes.h"


void DeepLayer::initializeLayer(const int& biasRange, const int& weightsRange, const int& currentLayer, const int& prevLayer)
{
	//std::cout << "> DL 1" << std::endl;//temp<<<<<<
	for (int i = 0; i < currentLayer; i++)
	{
		std::vector<double> newWeight;
		bias.push_back((random(2) - 1) * biasRange);
		//std::cout << "> DL bias " << i << std::endl;//temp<<<<<<
		for (int w = 0; w < prevLayer; w++)
		{
			newWeight.push_back((random(2) - 1) * weightsRange);
		}
		weights.push_back(newWeight);
		//std::cout << "> DL weights" << std::endl;//temp<<<<<<
	}
}
/*
void DeepLayer::calculateActivation(const std::vector<double>& inputNeurons)
{
	std::vector<double> outputNeurons;
	for (int i = 0; i < bias.size(); i++)
	{
		outputNeurons.push_back(sigmoid(singleWABprocessing(inputNeurons, weights[i], bias[i])));
	}
	modify_Neurons(outputNeurons);
}
*/
/*
void DeepLayer::calculateActivation(const std::vector<double>& inputNeurons)
{
	std::vector<double> outputNeurons;
	for (int i = 0; i < bias.size(); i++)
	{
		outputNeurons.push_back(sigmoid(singleWABprocessing(inputNeurons, weights[i], bias[i])));
	}
	add_Neurons(outputNeurons);
}

double DeepLayer::singleWABprocessing(const std::vector<double>& inputNeurons, const std::vector<double>& inputWeights, const double& inputbias)
{
	double holdNeuron = 0;
	for (int i = 0; i < inputWeights.size(); i++) holdNeuron += inputWeights[i] * inputNeurons[i];
	return holdNeuron + inputbias;
}
*/

////modify&return
void DeepLayer::modify_Bias(const std::vector<double>& newbias)
{
	bias.clear();
	bias = newbias;
}
void DeepLayer::modify_Weights(const std::vector<std::vector<double>>& newweights)
{
	weights.clear();
	weights = newweights;
}
std::vector<std::vector<double>> DeepLayer::return_Weights()
{
	return weights;
}
std::vector<double> DeepLayer::return_Bias()
{
	return bias;
}

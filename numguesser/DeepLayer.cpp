#include <random>
#include <chrono>

#include "classes.h"

class DeepLayer : public Layer
{
private:
	std::vector<double> bias;
	std::vector<std::vector<double>> weights;
public:
	void initializeLayer(const int& biasRange, const int& weightsRange, const int& currentLayer, const int& prevLayer)
	{
		for (int i = 0; i < currentLayer; i++)
		{
			std::vector<double> newWeight;
			bias.push_back((random(2) - 1) * biasRange);
			for (int w = 0; w < prevLayer; w++)
			{
				newWeight.push_back((random(2) - 1) * weightsRange);
			}
			weights.push_back(newWeight);
		}
	}
	void calculateActivation(const std::vector<double>& inputNeurons)
	{
		std::vector<double> outputNeurons;
		for (int i = 0; i < bias.size(); i++)
		{
			outputNeurons.push_back(sigmoid(singleWABprocessing(inputNeurons, weights[i], bias[i])));
		}
		modify_Neurons(outputNeurons);
	}
	double singleWABprocessing(const std::vector<double>& inputNeurons, const std::vector<double>& inputWeights, const double& inputbias)
	{
		double holdNeuron = 0;
		for (int i = 0; i < inputWeights.size(); i++) holdNeuron += inputWeights[i] * inputNeurons[i];
		return holdNeuron + inputbias;
	}
	////modify&return
	void modify_Bias(const std::vector<double>& newbias)
	{
		bias.clear();
		bias = newbias;
	}
	void modify_Weights(const std::vector<std::vector<double>>& newweights)
	{
		weights.clear();
		weights = newweights;
	}
	std::vector<std::vector<double>> return_Weights()
	{
		return weights;
	}
	std::vector<double> return_Bias()
	{
		return bias;
	}
};
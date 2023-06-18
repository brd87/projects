#include <random>
#include <chrono>

#include "classes.h"


void DeepLayer::initializeLayer(const int& biasRange, const int& weightsRange, const int& currentLayer, const int& prevLayer)
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
double DeepLayer::random(const int& range)
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> rozklad(0, range);
	return rozklad(engine);
}
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
void DeepLayer::kill_WAB()
{
	bias.clear();
	weights.clear();
}
DeepLayer& DeepLayer::operator-(ouBackprop& other) 
{
	std::vector<std::vector<double>> gradient = other.return_Gradient();
	for (int i = 0; i < bias.size(); i++) 
	{
		for (int n = 0; n < weights[i].size(); n++) 
		{
			this->weights[i][n] -= gradient[i][n];
		}
		this->bias[i] -= gradient[i][weights[i].size()];
	}
	return *this;
}
DeepLayer& DeepLayer::operator-(hiBackprop& other)
{
	std::vector<std::vector<double>> gradient = other.return_Gradient();
	for (int i = 0; i < bias.size(); i++)
	{
		for (int n = 0; n < weights[i].size(); n++)
		{
			this->weights[i][n] -= gradient[i][n];
		}
		this->bias[i] -= gradient[i][weights[i].size()];
	}
	return *this;
}


#include <vector>

#include "classes.h"

void ouBackprop::set(const int& size1, const int& size2)
{
	ouWABGradient = std::vector<std::vector<double>>(size1, std::vector<double>(size2 + 1));
}
void ouBackprop::backprop(const std::vector<double>& currentNeurons, const std::vector<double>& previusNeurons, const std::vector<std::vector<double>>& Weights, double* target)
{
	for (int i = 0; i < currentNeurons.size(); i++)
	{
		deltaOuLayer.push_back(sigmoidDerivative(currentNeurons[i]) * 2 * (currentNeurons[i] - target[i]));
		for (int n = 0; n < previusNeurons.size(); n++)
		{
			ouWABGradient[i][n] += previusNeurons[n] * deltaOuLayer[i];
			inputDer.push_back(Weights[i][n] * deltaOuLayer[i]);
		}
		ouWABGradient[i][previusNeurons.size()] += deltaOuLayer[i];
	}
}
void ouBackprop::lern(const double& learningRate)
{
	for (auto &i : ouWABGradient)
	{
		for (auto &n : i) n *= learningRate;
	}
}
std::vector<std::vector<double>> ouBackprop::return_Gradient()
{
	return ouWABGradient;
}
std::vector<double> ouBackprop::return_inputDer()
{
	return inputDer;
}
std::vector<double> ouBackprop::return_deltaOuLayer()
{
	return deltaOuLayer;
}
void ouBackprop::kill_inputDer()
{
	inputDer.clear();
}
void ouBackprop::kill_deltaOuLayer()
{
	deltaOuLayer.clear();
}
#include <vector>

#include "classes.h"

void hiBackprop::set(const int& size1, const int& size2)
{
	hiWABGradient = std::vector<std::vector<double>>(size1, std::vector<double>(size2 + 1));
}
void hiBackprop::backprop(const std::vector<double>& currentNeurons, const std::vector<double>& previusNeurons, const std::vector<std::vector<double>>& Weights, const std::vector<double>& deltaOu, const std::vector<double>& inputD, const int& size)
{
	for (int i = 0; i < currentNeurons.size(); i++)
	{
		double sumDeltaTimesWeight = 0.0;
		for (int n = 0; n < size; n++)
		{
			sumDeltaTimesWeight += Weights[n][i] * deltaOu[n];
		}
		double deltaHiLayer = sumDeltaTimesWeight * sigmoidDerivative(currentNeurons[i]) * inputD[i];
		for (int n = 0; n < previusNeurons.size(); n++)
		{
			hiWABGradient[i][n] += previusNeurons[n] * deltaHiLayer;
		}
		hiWABGradient[i][previusNeurons.size()] += deltaHiLayer;
	}
}
void hiBackprop::lern(const double& learningRate)
{
	for (auto& i : hiWABGradient)
	{
		for (auto& n : i) n *= learningRate;
	}
}
std::vector<std::vector<double>> hiBackprop::return_Gradient()
{
	return hiWABGradient;
}

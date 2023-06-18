#include <vector>
#include <random>
#include <iostream>

#include "classes.h"
#include "structures.h"

void Network::initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons)
{
	hiLayer.kill_WAB();
	ouLayer.kill_WAB();
	hiLayer.initializeLayer(2, 1, nHiddenNeurons, 784);
	ouLayer.initializeLayer(2, 1, nOutputNeurons, nHiddenNeurons);
}

void Network::forwardPropagation(const bool& mode)
{	
	int win = 0;
	for (int index = 0;index<minst.size();index++)
	{
		inLayer.add_Neurons(minst[index].pixels);
		std::vector<double> neuronSet = inLayer.return_Neurons(index);

		hiLayer.add_Neurons(calculateActivation(neuronSet, hiLayer.return_Weights(), hiLayer.return_Bias()));
		neuronSet = hiLayer.return_Neurons(index);

		ouLayer.add_Neurons(calculateActivation(neuronSet, ouLayer.return_Weights(), ouLayer.return_Bias()));
		neuronSet = ouLayer.return_Neurons(index);

		int guess = getOutput(neuronSet);
		if (guess == minst[index].label && mode) win++;
		if (!mode) std::cout << "Guessed number: " << guess << std::endl;
	}
	if (mode) std::cout << "BATCH WIN RATE: " << (100.0/minst.size())*win << "%\t" << win << "/" << minst.size() << std::endl;
}

void Network::backwardPropagation(const double& learningRate)
{
	std::vector<std::vector<double>> holdOuNeurons = ouLayer.return_allNeurons();
	std::vector<std::vector<double>> holdHiNeurons = hiLayer.return_allNeurons();
	std::vector<std::vector<double>> holdInNeurons = inLayer.return_allNeurons();
	std::vector<std::vector<double>> holdOuWeights = ouLayer.return_Weights();

	ouBackprop ouBack;
	hiBackprop hiBack;
	ouBack.set(holdOuNeurons[0].size(), holdHiNeurons[0].size());
	hiBack.set(holdHiNeurons[0].size(), holdInNeurons[0].size());
	
	for (int index = 0; index < minst.size(); index++)
	{
		double* target = minst[index].targetOutput;

		ouBack.backprop(holdOuNeurons[index],holdHiNeurons[index],holdOuWeights,target);
		hiBack.backprop(holdHiNeurons[index], holdInNeurons[index], holdOuWeights, ouBack.return_deltaOuLayer(), ouBack.return_inputDer(), holdOuNeurons[index].size());

		ouBack.kill_deltaOuLayer();
		ouBack.kill_inputDer();
	}
	ouBack.lern(learningRate);
	hiBack.lern(learningRate);
	updateWAB(ouBack, hiBack);
}

void Network::updateWAB(ouBackprop& ouGradient, hiBackprop& hiGradient)
{
	ouLayer = ouLayer - ouGradient;
	hiLayer = hiLayer - hiGradient;
}


void Network::epoch()
{
	kill_minst();
	inLayer.kill_neurons();
	hiLayer.kill_neurons();
	ouLayer.kill_neurons();
}

int Network::getOutput(const std::vector<double>& outputNeurons)
{
	int number = std::distance(outputNeurons.begin(), std::max_element(outputNeurons.begin(), outputNeurons.end()));
	return number;
}
//modify&return
void Network::modify_hiLayer(const DeepLayer& newhiLayer)
{
	hiLayer = newhiLayer;
}
void Network::modify_ouLayer(const DeepLayer& newouLayer)
{
	ouLayer = newouLayer;
}
void Network::modify_minst(const std::vector<MINSTdata>& newminst)
{
	minst.clear();
	minst = newminst;
}
void Network::add_minst(const MINSTdata& item)
{
	minst.push_back(item);
}
DeepLayer Network::return_hiLayer()
{
	return hiLayer;
}
DeepLayer Network::return_ouLayer()
{
	return ouLayer;
}
std::vector<MINSTdata> Network::return_minst()
{
	return minst;
}
void Network::kill_minst()
{
	minst.clear();
}
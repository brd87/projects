#include <vector>
#include <random>
#include <iostream>

#include "classes.h"
#include "structures.h"

void Network::initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons)
{
	//std::cout << "> WAB start_hi" << std::endl;
	hiLayer.initializeLayer(2, 1, nHiddenNeurons, 784);
	//std::cout << "> WAB start_ou" << std::endl;
	ouLayer.initializeLayer(2, 1, nOutputNeurons, nHiddenNeurons);
	//std::cout << "> WAB done" << std::endl;
}

void Network::forwardPropagation(const bool& mode)
{	
	//std::cout << ">> ForP start" << std::endl; //temp<<<<<<
	int win = 0;
	for (int index = 0;index<minst.size();index++)
	{
		//std::cout << "> ForP : " << index << std::endl; //temp<<<<<<
		inLayer.add_Neurons(minst[index].pixels);
		//std::cout << "> INdone : "; //temp<<<<<<
		std::vector<double> neuronSet = inLayer.return_Neurons(index);
		hiLayer.add_Neurons(calculateActivation(neuronSet, hiLayer.return_Weights(), hiLayer.return_Bias()));
		//std::cout << "HIdone : "; //temp<<<<<<
		neuronSet = hiLayer.return_Neurons(index);
		ouLayer.add_Neurons(calculateActivation(neuronSet, ouLayer.return_Weights(), ouLayer.return_Bias()));
		//std::cout << "OUdone" << std::endl; //temp<<<<<<
		std::vector<double> outputNeurons = ouLayer.return_Neurons(index);
		int guess = getOutput(outputNeurons);
		//std::cout << "Guessed number: " << guess << " should be: " << minst[index].label << std::endl;//temp<<<<<<
		if (guess == minst[index].label && mode) win++;
		if (!mode) std::cout << "Guessed number: " << guess << std::endl;
	}
	if (mode) std::cout << "WIN RATE: " << win << "/" << minst.size() << std::endl;
	//std::cout << "> IN : N-" << inLayer.return_Neurons(0).size() << std::endl; //temp<<<<<<
	//std::cout << "> HI : N-" << hiLayer.return_Neurons(0).size() << ", B-" << hiLayer.return_Bias().size()  << ", WpN-" << hiLayer.return_Weights()[0].size() << std::endl; //temp<<<<<<
	//std::cout << "> OU : N-" << ouLayer.return_Neurons(0).size()  << ", B-" << ouLayer.return_Bias().size() << ", WpN-" << ouLayer.return_Weights()[0].size() << std::endl; //temp<<<<<<
	//std::cout << ">> ForP done" << std::endl; //temp<<<<<<
}

void Network::backwardPropagation(const double& learningRate)
{
	std::cout << ">> BackP start" << std::endl; //temp<<<<<<
	std::vector<std::vector<double>> holdOuNeurons = ouLayer.return_allNeurons();
	std::vector<std::vector<double>> holdHiNeurons = hiLayer.return_allNeurons();
	std::vector<std::vector<double>> holdInNeurons = inLayer.return_allNeurons();
	std::vector<std::vector<double>> holdOuWeights = ouLayer.return_Weights();
	std::vector<std::vector<double>> holdHiWeights = hiLayer.return_Weights();
	double** ouWABGradient = new double* [holdOuNeurons[0].size()];
	double** ouXGradient = new double* [holdOuNeurons[0].size()];
	double** hiWABGradient = new double* [holdHiNeurons[0].size()];
	//double** hiXGradient = new double* [holdHiNeurons[0].size()];
	for (int i = 0; i < holdOuNeurons[0].size(); i++)
	{
		ouWABGradient[i] = new double[holdHiNeurons[0].size() + 1]();
		ouXGradient[i] = new double[holdHiNeurons[0].size()]();
	}
	for (int i = 0; i < holdHiNeurons[0].size(); i++)
	{
		hiWABGradient[i] = new double[holdInNeurons[0].size() + 1]();
		//hiXGradient[i] = new double[holdInNeurons[0].size()]();
	}
	for (int index = 0; index < minst.size(); index++)
	{
		std::vector<double> test;
		double* target = minst[index].targetOutput;
		double* deltaOuLayer = new double[holdOuNeurons[index].size()];
		for (int i = 0; i < holdOuNeurons[index].size(); i++)
		{
			deltaOuLayer[i] = sigmoidDerivative(holdOuNeurons[index][i]) * 2 * (holdOuNeurons[index][i] - target[i]);
			//std::cout << ">> BackP bump 2: " << i << std::endl; //temp<<<<<<
			for (int n = 0; n < holdHiNeurons[index].size(); n++)
			{
				ouWABGradient[i][n] += holdHiNeurons[index][n] * deltaOuLayer[i]; //backprop into weight
				//ouXGradient[i][n] += holdOuWeights[i][n] * deltaOuLayer[i]; //backprop into input
				test.push_back(holdOuWeights[i][n] * deltaOuLayer[i]);
			}
			ouWABGradient[i][holdHiNeurons[index].size()] += deltaOuLayer[i]; //backprop into bias
			//std::cout << ">> BackP bump 3: " << i << std::endl; //temp<<<<<<

		}
		//std::cout << ">> BackP ouPushed" << std::endl; //temp<<<<<<
		for (int i = 0; i < holdHiNeurons[index].size(); i++)
		{
			double sumDeltaTimesWeight = 0.0;
			for (int n = 0; n < holdOuNeurons[index].size(); n++)
			{
				sumDeltaTimesWeight += holdOuWeights[n][i] * deltaOuLayer[n];
			}
			double deltaHiLayer = sumDeltaTimesWeight * sigmoidDerivative(holdHiNeurons[index][i]) * test[i];
			//std::cout << "deltaHiLayer " << deltaHiLayer << std::endl;
			for (int n = 0; n < holdInNeurons[index].size(); n++)
			{
				hiWABGradient[i][n] += holdInNeurons[index][n] * deltaHiLayer; // backprop into weight
				//hiXGradient[i][n] += holdHiWeights[i][n] * deltaHiLayer; // backprop into input
			}
			hiWABGradient[i][holdInNeurons[index].size()] += deltaHiLayer; // backprop into bias
			//std::cout << ">> BackP bump 3: " << i << std::endl; //temp<<<<<<
		}
		test.clear();
		delete[] deltaOuLayer;
	}

	for (auto i : ouLayer.return_Bias()) std::cout << i << " | ";
	std::cout << std::endl;
	updateWAB(ouWABGradient, hiWABGradient, learningRate);
	for (auto i : ouLayer.return_Bias()) std::cout << i << " | ";
	std::cout << std::endl;

	for (int i = 0; i < holdOuNeurons[0].size(); i++)
	{
		delete[] ouWABGradient[i];
		delete[] ouXGradient[i];
	}
	for (int i = 0; i < holdHiNeurons[0].size(); i++)
	{
		delete[] hiWABGradient[i];
		//delete[] hiXGradient[i];
	}
	delete[] ouWABGradient;
	delete[] ouXGradient;
	delete[] hiWABGradient;
	//delete[] hiXGradient;
	//std::cout << ">> BackP done" << std::endl; //temp<<<<<<
}

void Network::updateWAB(double** ouWABGradient, double** hiWABGradient, const double& learningRate)
{
	//std::cout << ">> upWAB start" << std::endl; //temp<<<<<<
	int sizeOuNeurons = ouLayer.return_allNeurons()[0].size();
	int sizeHiNeurons = hiLayer.return_allNeurons()[0].size();
	int sizeInNeurons = inLayer.return_allNeurons()[0].size();
	std::vector<std::vector<double>> holdOuWeights = ouLayer.return_Weights();
	std::vector<double> holdOuBias = ouLayer.return_Bias();
	std::vector<std::vector<double>> holdHiWeights = hiLayer.return_Weights();
	std::vector<double> holdHiBias = hiLayer.return_Bias();

	for (int i = 0; i < sizeOuNeurons; i++) {
		for (int n = 0; n < sizeHiNeurons; n++) {
			holdOuWeights[i][n] -= learningRate * ouWABGradient[i][n];// / minst.size();
		}
		holdOuBias[i] -= learningRate * ouWABGradient[i][sizeHiNeurons];// / minst.size();
	}
	for (int i = 0; i < sizeHiNeurons; i++) {
		for (int n = 0; n < sizeInNeurons; n++) {
			holdHiWeights[i][n] -= learningRate * hiWABGradient[i][n];// / minst.size();
		}
		holdHiBias[i] -= learningRate * hiWABGradient[i][sizeInNeurons];// / minst.size();
	}
	ouLayer.modify_Weights(holdOuWeights);
	ouLayer.modify_Bias(holdOuBias);
	hiLayer.modify_Weights(holdHiWeights);
	hiLayer.modify_Bias(holdHiBias);
	inLayer.kill_neurons();
	hiLayer.kill_neurons();
	ouLayer.kill_neurons();

	//std::cout << ">> upWAB done" << std::endl; //temp<<<<<<
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
/*
void Network::modify_hiLayer(const HiddenLayer& newhiLayer)
{
	delete& hiLayer;
	hiLayer = newhiLayer;
}
void Network::modify_ouLayer(const OutputLayer& newouLayer)
{
	delete& ouLayer;
	ouLayer = newouLayer;
}
*/
void Network::modify_hiLayer(const DeepLayer& newhiLayer)
{
	//delete& hiLayer;
	hiLayer = newhiLayer;
}
void Network::modify_ouLayer(const DeepLayer& newouLayer)
{
	//delete& ouLayer;
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
/*
HiddenLayer Network::return_hiLayer()
{
	return hiLayer;
}
OutputLayer Network::return_ouLayer()
{
	return ouLayer;
}
*/
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
#include <vector>
#include <random>
#include <iostream>

#include "classes.h"
#include "structures.h"

void Network::initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons)
{
	std::cout << "> WAB start_hi" << std::endl;
	hiLayer.initializeLayer(2, 1, nHiddenNeurons, 784);
	std::cout << "> WAB start_ou" << std::endl;
	ouLayer.initializeLayer(2, 1, nOutputNeurons, nHiddenNeurons);
	std::cout << "> WAB done" << std::endl;
}
/*
void forwardPropagation(const int& example)
{
	inLayer.modify_Neurons(minst[example].pixels);
	std::vector<double> neuronSet = inLayer.return_Neurons();
	hiLayer.calculateActivation(neuronSet);
	neuronSet = hiLayer.return_Neurons();
	ouLayer.calculateActivation(neuronSet);
	std::vector<double> outputNeurons = ouLayer.return_Neurons();
	getOutput(outputNeurons);
}
*/
void Network::forwardPropagation()
{	
	std::cout << ">> ForP start" << std::endl; //temp<<<<<<
	for (int index = 0;index<minst.size();index++)
	{
		//std::cout << "> ForP : " << index << std::endl; //temp<<<<<<
		inLayer.add_Neurons(minst[index].pixels);
		//std::cout << "> INdone : "; //temp<<<<<<
		std::vector<double> neuronSet = inLayer.return_Neurons(index);
		//hiLayer.calculateActivation(neuronSet);
		hiLayer.add_Neurons(calculateActivation(neuronSet, hiLayer.return_Weights(), hiLayer.return_Bias()));
		//std::cout << "HIdone : "; //temp<<<<<<
		neuronSet = hiLayer.return_Neurons(index);
		//ouLayer.calculateActivation(neuronSet);
		ouLayer.add_Neurons(calculateActivation(neuronSet, ouLayer.return_Weights(), ouLayer.return_Bias()));
		//std::cout << "OUdone" << std::endl; //temp<<<<<<
		std::vector<double> outputNeurons = ouLayer.return_Neurons(index);
		getOutput(outputNeurons);
		std::cout << " should be: " << minst[index].label << std::endl;
	}
	std::cout << "> IN : N-" << inLayer.return_Neurons(0).size() << std::endl; //temp<<<<<<
	std::cout << "> HI : N-" << hiLayer.return_Neurons(0).size() << ", B-" << hiLayer.return_Bias().size()  << ", WpN-" << hiLayer.return_Weights()[0].size() << std::endl; //temp<<<<<<
	std::cout << "> OU : N-" << ouLayer.return_Neurons(0).size()  << ", B-" << ouLayer.return_Bias().size() << ", WpN-" << ouLayer.return_Weights()[0].size() << std::endl; //temp<<<<<<
	std::cout << ">> ForP done" << std::endl; //temp<<<<<<
}

/*
void Network::backwardPropagation(const int& example)
{
	std::vector<double> holdOuNeurons = ouLayer.return_Neurons();
	std::vector<double> holdHiNeurons = hiLayer.return_Neurons();
	std::vector<double> holdInNeurons = hiLayer.return_Neurons();
	double* target = minst[example].targetOutput;
	double** ouGradient = new double* [holdOuNeurons.size()];
	for (int i = 0; i < holdOuNeurons.size(); i++)
	{
		ouGradient[i] = new double[holdHiNeurons.size() + 1];
		for (int n = 0; n < holdHiNeurons.size(); n++)
		{
			ouGradient[i][n] = holdHiNeurons[n] * sigmoidDerivative(singleWABprocessing(holdHiNeurons, ouLayer.return_Weights()[i], ouLayer.return_Bias()[i])) * 2 * (holdOuNeurons[i] - target[i]);
		}
		ouGradient[i][holdHiNeurons.size()] = sigmoidDerivative(singleWABprocessing(holdHiNeurons, ouLayer.return_Weights()[i], ouLayer.return_Bias()[i])) * 2 * (holdOuNeurons[i] - target[i]);
	}
}
*/
void Network::backwardPropagation()
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
	double** hiXGradient = new double* [holdHiNeurons[0].size()];
	for (int i = 0; i < holdOuNeurons[0].size(); i++)
	{
		ouWABGradient[i] = new double[holdHiNeurons[0].size() + 1]();
		ouXGradient[i] = new double[holdHiNeurons[0].size()]();
	}
	for (int i = 0; i < holdHiNeurons[0].size(); i++)
	{
		hiWABGradient[i] = new double[holdInNeurons[0].size() + 1]();
		hiXGradient[i] = new double[holdInNeurons[0].size()]();
	}
    for (int index = 0; index < minst.size(); index++)
    {
		//double** ouWABGradient = new double* [holdOuNeurons[index].size()];
		//double** ouXGradient = new double* [holdOuNeurons[index].size()];
		//double** hiWABGradient = new double* [holdHiNeurons[index].size()];
		//double** hiXGradient = new double* [holdHiNeurons[index].size()];
        double* target = minst[index].targetOutput;
		double* deltaOuLayer = new double[holdOuNeurons[index].size()];
        for (int i = 0; i < holdOuNeurons[index].size(); i++)
        {
			//ouWABGradient[i] = new double[holdHiNeurons[index].size() + 1];
			//ouXGradient[i] = new double[holdHiNeurons[index].size()];
			//std::cout << ">> BackP bump 1: " << i << std::endl; //temp<<<<<<
			//std::cout << "> OU : N-" << holdHiNeurons[index].size() << ", WpN-" << ouLayer.return_Weights()[i].size() << std::endl; //temp<<<<<<
			
			//double deltaOu = sigmoidDerivative(holdOuNeurons[index][i]) * 2 * (holdOuNeurons[index][i] - target[i]);
			//deltaOuLayer[i] = deltaOu;
			deltaOuLayer[i] = sigmoidDerivative(holdOuNeurons[index][i]) * 2 * (holdOuNeurons[index][i] - target[i]);
			//std::cout << ">> BackP bump 2: " << i << std::endl; //temp<<<<<<
            for (int n = 0; n < holdHiNeurons[index].size(); n++)
            {
				ouWABGradient[i][n] += holdHiNeurons[index][n] * deltaOuLayer[i]; //backprop into weight
				ouXGradient[i][n] += holdOuWeights[i][n] * deltaOuLayer[i]; //backprop into input
            }
			ouWABGradient[i][holdHiNeurons[index].size()] += deltaOuLayer[i]; //backprop into bias
			//std::cout << ">> BackP bump 3: " << i << std::endl; //temp<<<<<<

        }
		//std::cout << ">> BackP ouPushed" << std::endl; //temp<<<<<<
		for (int i = 0; i < holdHiNeurons[index].size(); i++)
		{
			//hiWABGradient[i] = new double[holdInNeurons[index].size() + 1];
			//hiXGradient[i] = new double[holdInNeurons[index].size()];
			//std::cout << ">> BackP bump 1: " << i << std::endl; //temp<<<<<<
			//std::cout << "> HI : N-" << holdInNeurons[index].size() << ", WpN-" << hiLayer.return_Weights()[i].size() << std::endl; //temp<<<<<<
			double sumDeltaTimesWeight = 0.0;
			for (int n = 0; n < holdOuNeurons[index].size(); n++)
			{
				sumDeltaTimesWeight += holdOuWeights[n][i] * deltaOuLayer[n];
			}
			double deltaHiLayer = sumDeltaTimesWeight * sigmoidDerivative(holdHiNeurons[index][i]);
			//std::cout << ">> BackP bump 2: " << i << std::endl; //temp<<<<<<

			for (int n = 0; n < holdInNeurons[index].size(); n++)
			{
				hiWABGradient[i][n] += holdInNeurons[index][n] * deltaHiLayer; // backprop into weight
				hiXGradient[i][n] += holdHiWeights[i][n] * deltaHiLayer; // backprop into input
			}
			hiWABGradient[i][holdInNeurons[index].size()] += deltaHiLayer; // backprop into bias
			//std::cout << ">> BackP bump 3: " << i << std::endl; //temp<<<<<<
		}
		delete[] deltaOuLayer;
		//std::cout << ">> BackP hiPushed" << std::endl; //temp<<<<<<
		/*
		for (int i = 0; i < holdOuNeurons[index].size(); i++)
		{
			delete[] ouWABGradient[i];
			delete[] ouXGradient[i];
		}
		for (int i = 0; i < holdHiNeurons[index].size(); i++)
		{
			delete[] hiWABGradient[i];
			delete[] hiXGradient[i];
		}
		*/
	}
	updateWAB(ouWABGradient, ouXGradient, hiWABGradient, hiXGradient);
	for (int i = 0; i < holdOuNeurons[0].size(); i++)
    {
        delete[] ouWABGradient[i];
		delete[] ouXGradient[i];
    }
	for (int i = 0; i < holdHiNeurons[0].size(); i++)
	{
		delete[] hiWABGradient[i];
		delete[] hiXGradient[i];
	}
	delete[] ouWABGradient;
	delete[] ouXGradient;
	delete[] hiWABGradient;
	delete[] hiXGradient;
	std::cout << ">> BackP done" << std::endl; //temp<<<<<<
}

void Network::updateWAB(double** ouWABGradient, double** ouXGradient, double** hiWABGradient, double** hiXGradient)
{
	std::cout << ">> upWAB start" << std::endl; //temp<<<<<<
	int sizeOuNeurons = ouLayer.return_allNeurons()[0].size();
	int sizeHiNeurons = hiLayer.return_allNeurons()[0].size();
	int sizeInNeurons = inLayer.return_allNeurons()[0].size();
	std::vector<std::vector<double>> holdOuWeights = ouLayer.return_Weights();
	std::vector<double> holdOuBias = ouLayer.return_Bias();
	std::vector<std::vector<double>> holdHiWeights = hiLayer.return_Weights();
	std::vector<double> holdHiBias = hiLayer.return_Bias();

	for (int i = 0; i < sizeOuNeurons; i++) {
		for (int n = 0; n < sizeHiNeurons; n++) {
			holdOuWeights[i][n] -= ouWABGradient[i][n]/minst.size();
		}
		holdOuBias[i] -= ouWABGradient[i][sizeHiNeurons]/minst.size();
	}
	for (int i = 0; i < sizeHiNeurons; i++) {
		for (int n = 0; n < sizeInNeurons; n++) {
			holdHiWeights[i][n] -= hiWABGradient[i][n]/minst.size();
		}
		holdHiBias[i] -= hiWABGradient[i][sizeInNeurons]/minst.size();
	}
	ouLayer.modify_Weights(holdOuWeights);
	ouLayer.modify_Bias(holdOuBias);
	hiLayer.modify_Weights(holdHiWeights);
	hiLayer.modify_Bias(holdHiBias);
	std::cout << ">> upWAB done" << std::endl; //temp<<<<<<
}

void Network::epoch()
{
	kill_minst();
	inLayer.kill_neurons();
	hiLayer.kill_neurons();
	ouLayer.kill_neurons();
}

void Network::getOutput(const std::vector<double>& outputNeurons)
{
	int number = std::distance(outputNeurons.begin(), std::max_element(outputNeurons.begin(), outputNeurons.end()));
	std::cout << "Guessed number: " << number;
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
	delete& hiLayer;
	hiLayer = newhiLayer;
}
void Network::modify_ouLayer(const DeepLayer& newouLayer)
{
	delete& ouLayer;
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
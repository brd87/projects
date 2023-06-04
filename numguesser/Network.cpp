#include <vector>
#include <random>
#include <iostream>

#include "classes.h"
#include "structures.h"

class Network : public DeepLayer
{
private:
	std::vector<MINSTdata> minst;
	//InputLayer inLayer;
	//HiddenLayer hiLayer;
	//OutputLayer ouLayer;
	Layer inLayer;
	DeepLayer hiLayer;
	DeepLayer ouLayer;
	//std::vector<Layer> layers;
public:

	void initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons)
	{
		hiLayer.initializeLayer(2, 1, nHiddenNeurons, nHiddenNeurons);
		ouLayer.initializeLayer(2, 1, nOutputNeurons, nHiddenNeurons);
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
	void forwardPropagation()
	{	
		for (int index = 0;index<minst.size();index++)
		{
			inLayer.add_Neurons(minst[index].pixels);
			std::vector<double> neuronSet = inLayer.return_Neurons(index);
			hiLayer.calculateActivation(neuronSet);
			neuronSet = hiLayer.return_Neurons(index);
			ouLayer.calculateActivation(neuronSet);
			std::vector<double> outputNeurons = ouLayer.return_Neurons(index);
			getOutput(outputNeurons);
		}
	}

	/*
	void backwardPropagation(const int& example)
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
	void backwardPropagation()
	{
		std::vector<std::vector<double>> holdOuNeurons = ouLayer.return_allNeurons();
		std::vector<std::vector<double>> holdHiNeurons = hiLayer.return_allNeurons();
		std::vector<std::vector<double>> holdInNeurons = hiLayer.return_allNeurons();
		for (int index = 0; index < minst.size(); index++)
		{
			
			double* target = minst[index].targetOutput;
			double** ouGradient = new double* [holdOuNeurons[index].size()];
			for (int i = 0; i < holdOuNeurons.size(); i++)
			{
				ouGradient[i] = new double[holdHiNeurons[index].size() + 1];
				for (int n = 0; n < holdHiNeurons[index].size(); n++)
				{
					ouGradient[i][n] = holdHiNeurons[index][n] * sigmoidDerivative(singleWABprocessing(holdHiNeurons[index], ouLayer.return_Weights()[i], ouLayer.return_Bias()[i]))
						* 2 * (holdOuNeurons[index][i] - target[i]);
				}
				ouGradient[i][holdHiNeurons[index].size()] = sigmoidDerivative(singleWABprocessing(holdHiNeurons[index], ouLayer.return_Weights()[i], ouLayer.return_Bias()[i]))
					* 2 * (holdOuNeurons[index][i] - target[i]);
			}
		}
	}

	void updateWAB()
	{

	}

	void epoch(const int& nEpoch)
	{
		for (int i = 0; i < nEpoch; i++)
		{
			backwardPropagation();
			updateWAB();
		}
		kill_minst();
		inLayer.kill_neurons();
		hiLayer.kill_neurons();
		ouLayer.kill_neurons();
	}

	std::vector<double> getOutput(const std::vector<double>& outputNeurons)
	{
		int number = std::distance(outputNeurons.begin(), std::max_element(outputNeurons.begin(), outputNeurons.end()));
		std::cout << "Guessed number: " << number << std::endl;
	}
	//modify&return
	/*
	void modify_hiLayer(const HiddenLayer& newhiLayer)
	{
		delete& hiLayer;
		hiLayer = newhiLayer;
	}
	void modify_ouLayer(const OutputLayer& newouLayer)
	{
		delete& ouLayer;
		ouLayer = newouLayer;
	}
	*/
	void modify_hiLayer(const DeepLayer& newhiLayer)
	{
		delete& hiLayer;
		hiLayer = newhiLayer;
	}
	void modify_ouLayer(const DeepLayer& newouLayer)
	{
		delete& ouLayer;
		ouLayer = newouLayer;
	}
	void modify_minst(const std::vector<MINSTdata>& newminst)
	{
		minst.clear();
		minst = newminst;
	}
	/*
	HiddenLayer return_hiLayer()
	{
		return hiLayer;
	}
	OutputLayer return_ouLayer()
	{
		return ouLayer;
	}
	*/
	DeepLayer return_hiLayer()
	{
		return hiLayer;
	}
	DeepLayer return_ouLayer()
	{
		return ouLayer;
	}
	std::vector<MINSTdata> return_minst()
	{
		return minst;
	}
	void kill_minst()
	{
		minst.clear();
	}
};
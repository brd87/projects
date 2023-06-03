#ifndef CLASSES_H
#define CLASSES_H

#include <vector>

#include "functions.h"

//used database: https://www.kaggle.com/datasets/oddrationale/mnist-in-csv?resource=download
//"n" before fild names states for "number of"
//"WAB" states for "Weights And Biases"
class Layer
{
private:
	std::vector<double> neurons;
public:
    double sigmoid(const double& neuron);
    double sigmoidDerivative(const double& neuron);

	////modify&return
	void modify_Neurons(const std::vector<double>& newNeurons);
	std::vector<double> return_Neurons();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class DeepLayer : public Layer
{
private:
    std::vector<double> bias;
    std::vector<std::vector<double>> weights;

public:
    void initializeLayer(const int& biasRange, const int& weightsRange, const int& currentLayer, const int& prevLayer);
    void calculateActivation(const std::vector<double>& inputNeurons);
    double singleWABprocessing(const std::vector<double>& inputNeurons, const std::vector<double>& inputWeights, const double& inputBias);
    void modify_Bias(const std::vector<double>& newBias);
    void modify_Weights(const std::vector<std::vector<double>>& newWeights);
    std::vector<std::vector<double>> return_Weights();
    std::vector<double> return_Bias();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class Network : public DeepLayer
{
private:
	std::vector<MINSTdata> minst;
	//InputLayer inLayer;
	//HiddenLayer hiLayer;
	//OutputLayer ouLayer;
	//std::vector<Layer> layers;
	Layer inLayer;
	DeepLayer hiLayer;
	DeepLayer ouLayer;
public:
	void initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons);
	void forwardPropagation(const int& example);
	void backwardPropagation(const int& example);
	void updateWAB();
	std::vector<double> getOutput(const std::vector<double>& outputNeurons);
	//void modify_hiLayer(const HiddenLayer& newhiLayer);
	//void modify_ouLayer(const OutputLayer& newouLayer);
	void modify_hiLayer(const DeepLayer& newhiLayer);
	void modify_ouLayer(const DeepLayer& newouLayer);
	void modify_minst(const std::vector<MINSTdata>& newminst);
	//HiddenLayer return_hiLayer();
	//OutputLayer return_ouLayer();
	DeepLayer return_hiLayer();
	DeepLayer return_ouLayer();
	std::vector<MINSTdata> return_minst();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class Menu
{
private:
	Network network;
public:

	void start();
	void loadWAB(const std::string& fileName);
	void train(const std::string& fileName, const int& nHiLayerNeurons);
	void saveWAB(const std::string& fileName);
	void feed(const std::string& fileName);
};
#endif
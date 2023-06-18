#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <string>

#include "structures.h"

//used database: https://www.kaggle.com/datasets/oddrationale/mnist-in-csv?resource=download
//"n" before fild names states for "number of"
//"WAB" states for "Weights And Biases"

class Layer
{
private:
	std::vector<std::vector<double>> neurons;
public:
	void modify_Neurons(const int& index, const std::vector<double>& newNeurons);
	void add_Neurons(const std::vector<double>& newNeurons);
	std::vector<double> return_Neurons(const int& index);
	std::vector<std::vector<double>> return_allNeurons();
	void kill_neurons();
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class Processing
{
private:
	std::vector<std::vector<double>> gradient;
public:
	std::vector<double> calculateActivation(const std::vector<double>& inputNeurons, const std::vector<std::vector<double>>& weights, const std::vector<double>& bias);
	double singleWABprocessing(const std::vector<double>& inputNeurons, const std::vector<double>& inputWeights, const double& inputbias);
	double sigmoid(const double& neuron);
	double sigmoidDerivative(const double& neuron);
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class ouBackprop : public Processing
{
private:
	std::vector<std::vector<double>> ouWABGradient;
	std::vector<double> inputDer;
	std::vector<double> deltaOuLayer;
public:
	void set(const int& size1, const int& size2);
	void backprop(const std::vector<double>& currentNeurons, const std::vector<double>& previusNeurons, const std::vector<std::vector<double>>& Weights, double* target);
	void lern(const double& learningRate);
	std::vector<std::vector<double>> return_Gradient();
	std::vector<double> return_inputDer();
	std::vector<double> return_deltaOuLayer();
	void kill_inputDer();
	void kill_deltaOuLayer();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class hiBackprop : public Processing
{
private:
	std::vector<std::vector<double>> hiWABGradient;
public:
	void set(const int& size1, const int& size2);
	void backprop(const std::vector<double>& currentNeurons, const std::vector<double>& previusNeurons, const std::vector<std::vector<double>>& Weights, const std::vector<double>& deltaOu, const std::vector<double>& inputD, const int& size);
	void lern(const double& learningRate);
	std::vector<std::vector<double>> return_Gradient();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class DeepLayer : public Layer
{
private:
    std::vector<double> bias;
    std::vector<std::vector<double>> weights;
public:
    void initializeLayer(const int& biasRange, const int& weightsRange, const int& currentLayer, const int& prevLayer);
    double random(const int& range);
	void modify_Bias(const std::vector<double>& newBias);
    void modify_Weights(const std::vector<std::vector<double>>& newWeights);
    std::vector<std::vector<double>> return_Weights();
    std::vector<double> return_Bias();
	void kill_WAB();
	DeepLayer& operator-(ouBackprop& other);
	DeepLayer& operator-(hiBackprop& other);
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class Network : public Processing
{
private:
	std::vector<MINSTdata> minst;
	Layer inLayer;
	DeepLayer hiLayer;
	DeepLayer ouLayer;
public:
	void initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons);
	void forwardPropagation(const bool& mode);
	void backwardPropagation(const double& learningRate);
	void updateWAB(ouBackprop& ouGradient, hiBackprop& hiGradient);
	void epoch();
	int getOutput(const std::vector<double>& outputNeurons);
	void modify_hiLayer(const DeepLayer& newhiLayer);
	void modify_ouLayer(const DeepLayer& newouLayer);
	void modify_minst(const std::vector<MINSTdata>& newminst);
	void add_minst(const MINSTdata& item);
	DeepLayer return_hiLayer();
	DeepLayer return_ouLayer();
	std::vector<MINSTdata> return_minst();
	void kill_minst();
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
class Menu
{
private:
	Network network;
public:
	void start();
	void loadWAB(const std::string& fileName);
	void train(const std::string& fileName, const int& nHiLayerNeurons, const int& batchSize, const int& epochSize, const double& learningRate, const bool& initialize, const int& batchRange);
	void saveWAB(const std::string& fileName);
	void feed(const std::string& fileName, const int& task);
};
#endif
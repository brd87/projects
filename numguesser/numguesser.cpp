#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
//"n" before fild names states for "number of"
//"WAB" states for "Weights And Biases"
/////////////////////////////////////////////////////////////////////////////
struct MINSTdata
{
	int label;
	std::vector<double> pixels;
	double targetOutput[10] = {0};
};
double random(const int& range)
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::normal_distribution<double> rozklad(0, range);
	return rozklad(engine);
}
/////////////////////////////////////////////////////////////////////////////
class Layer
{
private:
	std::vector<double> neurons;
	//std::vector<double> derivedNeurons;
public:
	double sigmoid(const double& sNeuron)
	{
		return 1 / (1 + exp(sNeuron));
	}
	double sigmoidDerivative(const double& sNeuron)
	{
		return sigmoid(sNeuron) * (1 - sigmoid(sNeuron));
	}
	/*
	void derNeurons()
	{
		for (auto i : neurons)
		{
			derivedNeurons.push_back(sigmoidDerivative(i));
		}
	}
	*/
	
	////modify&return
	void modify_Neurons(const std::vector<double>& newneurons)
	{
		neurons.clear();
		neurons = newneurons;
	}
	std::vector<double> return_Neurons()
	{
		return neurons;
	}
};
/////////////////////////////////////////////////////////////////////////////
class DeepLayer : public Layer
{
private:
	std::vector<double> bias;
	std::vector<std::vector<double>> weights;
public:
	void initializeLayer(const int& frange, const int& srange, const int& currentLayer, const int& prevLayer)
	{
		for (int i = 0; i < currentLayer; i++)
		{
			std::vector<double> nweight;
			bias.push_back((random(2) - 1) * frange);
			for (int w = 0; w < prevLayer; w++)
			{
				nweight.push_back((random(2) - 1) * srange);
			}
			weights.push_back(nweight);
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
/////////////////////////////////////////////////////////////////////////////
class InputLayer : public Layer
{

};
/////////////////////////////////////////////////////////////////////////////
class HiddenLayer : public DeepLayer
{

};
/////////////////////////////////////////////////////////////////////////////
class OutputLayer : public DeepLayer
{

};
/////////////////////////////////////////////////////////////////////////////
class Network : public DeepLayer
{
private:
	std::vector<MINSTdata> minst;
	InputLayer inLayer;
	HiddenLayer hiLayer;
	OutputLayer ouLayer;
	std::vector<Layer> layers;
	//int nHiddenLayers;
public:
	//int nInput;
	//int nOutput;
	//int nHiddenLayers;
	//int nHiddenNeurons;
	//int nOutputNeurons;

	void initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons)
	{
		//layers.push_back(inLayer);
		//for (int i = 0; i < nHiddenLayers; i++)
		//	layers.push_back();
		/*
		for (auto& layer : hiLayers)
		{
			layer.initializeLayer(2, 1, nHiddenNeurons, nHiddenNeurons);

		}
		*/
		hiLayer.initializeLayer(2, 1, nHiddenNeurons, nHiddenNeurons);
		ouLayer.initializeLayer(2, 1, nOutputNeurons, nHiddenNeurons);
	}

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

	void updateWAB()
	{

	}

	std::vector<double> getOutput(const std::vector<double>& outputNeurons)
	{
		int number = std::distance(outputNeurons.begin(), std::max_element(outputNeurons.begin(), outputNeurons.end()));
		std::cout << "Guessed number: " << number << std::endl;
	}
	//modify&return
	/*
	void modify_hiLayers(const std::vector<HiddenLayer>& newhiLayers)
	{
		hiLayers.clear();
		hiLayers = newhiLayers;
	}
	*/
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
	void modify_minst(const std::vector<MINSTdata>& newminst)
	{
		minst.clear();
		minst = newminst;
	}
	/*
	std::vector<HiddenLayer> return_hiLayers()
	{
		return hiLayers;
	}
	*/
	HiddenLayer return_hiLayer()
	{
		return hiLayer;
	}
	OutputLayer return_ouLayer()
	{
		return ouLayer;
	}
	std::vector<MINSTdata> return_minst()
	{
		return minst;
	}
};
/////////////////////////////////////////////////////////////////////////////
class Menu
{
private:
	Network network;
public:

	void start()
	{

	}

	void loadWAB(const std::string& fileName)
	{
		//std::vector<HiddenLayer> hold_hiLayers;
		OutputLayer hold_ouLayer;
		HiddenLayer hold_hiLayer;
		std::vector<double> hold_bias;
		std::vector<double> hold_nuronWeights;
		std::vector<std::vector<double>> hold_weights;
		std::ifstream file(fileName);
		std::string line;
		std::string value;
		bool isH = false;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				if (line == "W")
				{
					if (isH)
					{
						hold_hiLayer.modify_Bias(hold_bias);
						hold_hiLayer.modify_Weights(hold_weights);
						//hold_hiLayers.push_back(hold_hiLayer);
					}
					else
					{
						hold_ouLayer.modify_Bias(hold_bias);
						hold_ouLayer.modify_Weights(hold_weights);
					}
					isH = 1;
					hold_bias.clear();
					hold_weights.clear();
					continue;
				}
				std::stringstream ss(line);
				hold_nuronWeights.clear();
				std::getline(ss, value, ',');
				hold_bias.push_back(std::stod(value));
				while (std::getline(ss, value, ','))
				{
					hold_nuronWeights.push_back(std::stod(value));
				}
				hold_weights.push_back(hold_nuronWeights);
			}
			file.close();
			//network.modify_hiLayers(hold_hiLayers);
			network.modify_hiLayer(hold_hiLayer);
			network.modify_ouLayer(hold_ouLayer);
		}
		else
		{
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}

	void train(const std::string& fileName, const int& nHiLayerNeurons)
	{
		std::vector<MINSTdata> minst;
		std::ifstream file(fileName);
		std::string line;
		std::string value;
		if (file.is_open())
		{
			std::getline(file, line);
			while (std::getline(file, line))
			{
				MINSTdata item;
				std::stringstream ss(line);
				std::getline(ss, value, ',');
				item.label = std::stoi(value);
				item.targetOutput[item.label] = 1;
				while (std::getline(ss, value, ','))
				{
					item.pixels.push_back(std::stoi(value));
				}
				minst.push_back(item);
			}
			network.modify_minst(minst);
			file.close();
			network.initializeWAB(nHiLayerNeurons, 10);
			for (int i=0;i< network.return_minst().size();i++)
			{
				network.forwardPropagation(i);
				network.backwardPropagation(i);
			}
		}
		else
		{
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}

	void saveWAB(const std::string& fileName)
	{
		std::vector<std::vector<double>> weights;
		std::vector<double> bias;
		std::ofstream file(fileName);
		if (file.is_open())
		{
			weights = network.return_ouLayer().return_Weights();
			bias = network.return_ouLayer().return_Bias();
			for (int i = 0; i < bias.size(); i++)
			{
				file << bias[i] << ",";
				for (auto n : weights[i]) file << n << ",";
				file << "\n";
			}
			file << "W\n";
			weights = network.return_hiLayer().return_Weights();
			bias = network.return_hiLayer().return_Bias();
			for (int i = 0; i < bias.size(); i++)
			{
				file << bias[i] << ",";
				for (auto n : weights[i]) file << n << ",";
				file << "\n";
			}
			/*
			for (auto& leyer : network.return_hiLayers())
			{
				weights = leyer.return_Weights();
				bias = leyer.return_Bias();
				file << "W\n";
				for (int i = 0; i < bias.size(); i++)
				{
					file << bias[i] << ",";
					for (auto n : weights[i]) file << n << ",";
					file << "\n";
				}
			}
			*/

			file.close();
		}
		else {
			std::cout << "Error: Failed to open a file." << std::endl;
		}
	}

	void feed(const std::string& fileName) {
		MINSTdata item;
		std::ifstream file(fileName);
		std::string line;
		std::string value;
		if (file.is_open())
		{
			std::getline(file, line);
			std::stringstream ss(line);
			std::getline(ss, value, ',');
			item.label = std::stoi(value);
			while (std::getline(ss, value, ','))
			{
				item.pixels.push_back(std::stoi(value));
			}
			file.close();
		}
		else
		{
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}
};
/////////////////////////////////////////////////////////////////////////////
int main()
{
	std::cout << "NETWORK";
	Menu Test;
	Test.train("mnist_train.csv", 1000);
	std::cout << "File loaded";
	return 0;
}
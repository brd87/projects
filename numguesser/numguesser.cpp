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
	std::vector<int> pixels;
};
double random(const int& range)
{ // <--- MOŻE SIĘ ZEPSUĆ
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	//std::uniform_real_distribution<double> rozklad(0, range);
	std::normal_distribution<double> rozklad(0, range);
	return rozklad(engine);
}
/////////////////////////////////////////////////////////////////////////////
class Layer
{
private:
	std::vector<double> neurons;
public:
	void modify_Neurons(const std::vector<double>& newneurons)
	{
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
		for (int i; i < currentLayer; i++)
		{
			std::vector<double> nweight;
			bias.push_back((random(2) - 1) * frange);
			for (int w; w < prevLayer; w++)
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
			//double holdNeuron=0;
			//for (int w = 0; w < weights[i].size();w++) holdNeuron += weights[i][w] * inputNeurons[i];
			//outputNeurons.push_back(sigmoid(holdNeuron + bias[i]));
			outputNeurons.push_back(sigmoid(singleWABprocessing(inputNeurons[i], weights[i], bias[i])));
		}
		modify_Neurons(outputNeurons);
	}
	double sigmoid(const double& sNeuron)
	{
		return 1 / (1 + exp(sNeuron));
	}
	double sigmoidDerivative(const double& sNeuron)
	{
		return sigmoid(sNeuron) * (1 - sigmoid(sNeuron));
	}
	double singleWABprocessing(const double& inputNeuron, const std::vector<double>& inputWeights, const double& inputbias)
	{
		double holdNeuron = 0;
		for (int i = 0; i < inputWeights.size(); i++) holdNeuron += inputWeights[i] * inputNeuron;
		return holdNeuron+inputbias;
	}
	////modify&return
	void modify_Bias(const std::vector<double>& newbias)
	{
		bias = newbias;
	}
	void modify_Weights(const std::vector<std::vector<double>>& newweights)
	{
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
	InputLayer inLayers;
	std::vector<HiddenLayer> hiLayers;
	OutputLayer ouLayer;
public:
	//int nInput;
	//int nOutput;
	//int nHiddenLayers;
	//int nHiddenNeurons;
	//int nOutputNeurons;

	void initializeWAB(const int& nHiddenNeurons, const int& nOutputNeurons)
	{
		for (auto &layer : hiLayers)
		{
			layer.initializeLayer(2, 1, nHiddenNeurons, nHiddenNeurons);
		}
		ouLayer.initializeLayer(2, 1, nOutputNeurons, nHiddenNeurons);
	}

	void forwardPropagation()
	{
		std::vector<double> neuronSet = inLayers.return_Neurons();
		for (auto layer : hiLayers)
		{
			layer.calculateActivation(neuronSet);
			neuronSet = layer.return_Neurons();
		}
		ouLayer.calculateActivation(neuronSet);
	}

	void backwardPropagation()
	{
		HiddenLayer lasthiLayer = hiLayers.back();
		int target;
		double gradient = 0;
		for (int i=0; i < ouLayer.return_Neurons().size(); i++)
		{
			target = 0;
			if (minst[i].label == i) target = 1;
			for(int n=0; n < lasthiLayer.return_Neurons().size();n++)
			{
				gradient += lasthiLayer.return_Neurons()[n] * sigmoidDerivative(singleWABprocessing(lasthiLayer.return_Neurons()[n], lasthiLayer.return_Weights()[n],lasthiLayer.return_Bias()[n])) * 2 * (ouLayer.return_Neurons()[i] - target);
			}
		}
	}

	void updateWAB()
	{

	}

	std::vector<double> getOutput()
	{

	}
	//modify&return
	void modify_hiLayers(const std::vector<HiddenLayer>& newhiLayers)
	{
		hiLayers = newhiLayers;
	}
	void modify_ouLayer(const OutputLayer& newouLayer)
	{
		ouLayer = newouLayer;
	}
	void modify_minst(const std::vector<MINSTdata>& newminst)
	{
		minst = newminst;
	}
	std::vector<HiddenLayer> return_hiLayers()
	{
		return hiLayers;
	}
	OutputLayer return_ouLayer()
	{
		return ouLayer;
	}
};
/////////////////////////////////////////////////////////////////////////////
class Menu
{
private:
	Network network;
	//std::vector<MINSTdata> minst;
public:

	void start()
	{

	}

	void loadWAB(const std::string& fileName)
	{
		std::vector<HiddenLayer> hold_hiLayers;
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
						hold_hiLayers.push_back(hold_hiLayer);
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
			network.modify_hiLayers(hold_hiLayers);
			network.modify_ouLayer(hold_ouLayer);
		}
		else
		{
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}

	void train(const std::string& fileName)
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
				while (std::getline(ss, value, ','))
				{
					item.pixels.push_back(std::stoi(value));
				}
				minst.push_back(item);
			}
			network.modify_minst(minst);
			file.close();
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
			file.close();
		}
		else {
			std::cout << "Error: Failed to open a file." << std::endl;
		}
	}

	void feed(const std::string& fileName) {
		std::vector<MINSTdata> minst;
		std::ifstream file(fileName);
		std::string line;
		std::string value;
		if (file.is_open())
		{
			std::getline(file, line);
			MINSTdata item;
			std::stringstream ss(line);
			std::getline(ss, value, ',');
			item.label = std::stoi(value);
			while (std::getline(ss, value, ','))
			{
				item.pixels.push_back(std::stoi(value));
			}
			minst.push_back(item);
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
	Test.train("mnist_train.csv");
	std::cout << "AAAAA";
	return 0;
}
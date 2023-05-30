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
double random(const int& range) { // <--- MOŻE SIĘ ZEPSUĆ
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
	//Layer nextlayer;
	int nNeurons;
	void setNeuronActivation(int neuronIndex, double activation) {

	}
	std::vector<double> return_neurons() {
		return neurons;
	}
};
/////////////////////////////////////////////////////////////////////////////
class DeepLayer : public Layer {
private:
	std::vector<double> bias;
	std::vector<std::vector<double>> weights;
public:
	void initializeLayer(const int& frange, const int& srange, const int& Nnum) {
		for (int i; i < Nnum; i++)
		{
			std::vector<double> nweight;
			bias.push_back((random(2) - 1) * frange);
			for (int w; w < Nnum; w++)
			{
				nweight.push_back((random(2) - 1) * srange);
			}
			weights.push_back(nweight);
		}
	}
	std::vector<double> calculateActivation(const std::vector<double>& inputNeurons) {
		std::vector<double> outputNeurons;
		for (int i = 0; i < bias.size(); i++)
		{
			double holdNeuron=0;
			for (auto w : weights[i].size()) holdNeuron += weights[i][w] * inputNeurons[i];
			outputNeurons.push_back(holdNeuron + bias[i]);
		}
		return outputNeurons;
	}
	////modify&return
	void modify_Bias(const std::vector<double>& newbias) {
		bias = newbias;
	}
	void modify_Weights(const std::vector<std::vector<double>>& newweights) {
		weights = newweights;
	}
	std::vector<std::vector<double>> return_Weights() {
		return weights;
	}
	std::vector<double> return_Bias() {
		return bias;
	}
};
/////////////////////////////////////////////////////////////////////////////
class InputLayer : public Layer {

};
/////////////////////////////////////////////////////////////////////////////
class HiddenLayer : public DeepLayer {

};
/////////////////////////////////////////////////////////////////////////////
class OutputLayer : public DeepLayer {

};
/////////////////////////////////////////////////////////////////////////////
class Network {
private:
	InputLayer inLayers;
	std::vector<HiddenLayer> hiLayers;
	OutputLayer ouLayer;
public:
	int nInput;
	int nOutput;
	int nHiddenLayers;
	int nHiddenNeurons;
	int nOutputNeurons;

	void initializeWAB() {
		for (auto layer : hiLayers) {
			layer.initializeLayer(2, 1, nHiddenNeurons);
		}
		ouLayer.initializeLayer(2, 1, nOutputNeurons);
	}

	void forwardPropagation() {

	}

	void backwardPropagation() {

	}

	void updateWAB() {

	}

	std::vector<double> getOutput() {
	}
	//modify&return
	void modify_hiLayers(const std::vector<HiddenLayer>& newhiLayers) {
		hiLayers = newhiLayers;
	}
	void modify_ouLayer(const OutputLayer& newouLayer) {
		ouLayer = newouLayer;
	}
	std::vector<HiddenLayer> return_hiLayers() {
		return hiLayers;
	}
	OutputLayer return_ouLayer() {
		return ouLayer;
	}
};
/////////////////////////////////////////////////////////////////////////////
class Menu {
private:
	Network network;
public:

	void start() {
	}

	void loadWAB(const std::string& fileName) {
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
		if (file.is_open()) {
			while (std::getline(file, line)) {
				if (line == "W") {
					if (isH) {
						hold_hiLayer.modify_Bias(hold_bias);
						hold_hiLayer.modify_Weights(hold_weights);
						hold_hiLayers.push_back(hold_hiLayer);
					}
					else {
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
				while (std::getline(ss, value, ',')) {
					hold_nuronWeights.push_back(std::stod(value));
				}
				hold_weights.push_back(hold_nuronWeights);
			}
			file.close();
			network.modify_hiLayers(hold_hiLayers);
			network.modify_ouLayer(hold_ouLayer);
		}
		else {
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}

	void train(const std::string& fileName) {
		std::vector<MINSTdata> minst;
		std::ifstream file(fileName);
		std::string line;
		std::string value;
		if (file.is_open()) {
			while (std::getline(file, line)) {
				MINSTdata item;
				std::stringstream ss(line);
				std::getline(ss, value, ',');
				item.label = std::stoi(value);
				while (std::getline(ss, value, ',')) {
					item.pixels.push_back(std::stoi(value));
				}
				minst.push_back(item);
			}
			file.close();
		}
		else {
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}

	void saveWAB(const std::string& fileName) {
		std::vector<std::vector<double>> weights;
		std::vector<double> bias;
		std::ofstream file(fileName);
		if (file.is_open()) {
			weights = network.return_ouLayer().return_Weights();
			bias = network.return_ouLayer().return_Bias();
			for (int i = 0; i < bias.size(); i++)
			{
				file << bias[i] << ",";
				for (auto n : weights[i]) file << n << ",";
				file << "\n";
			}
			for (auto& leyer : network.return_hiLayers()) {
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
		if (file.is_open()) {
			std::getline(file, line);
			MINSTdata item;
			std::stringstream ss(line);
			std::getline(ss, value, ',');
			item.label = std::stoi(value);
			while (std::getline(ss, value, ',')) {
				item.pixels.push_back(std::stoi(value));
			}
			minst.push_back(item);
			file.close();
		}
		else {
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}
};
/////////////////////////////////////////////////////////////////////////////
int main()
{
	std::cout << "NETWORK";
}
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "classes.h"
#include "structures.h"

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
		//OutputLayer hold_ouLayer;
		//HiddenLayer hold_hiLayer;
		DeepLayer hold_ouLayer;
		DeepLayer hold_hiLayer;
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

	void train(const std::string& fileName, const int& nHiLayerNeurons, const int& batchSize, const int& nEpoch)
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

			//temporary placement
			network.initializeWAB(nHiLayerNeurons, 10);
			network.forwardPropagation();
			network.epoch(nEpoch);
			/*
			for (int i = 0; i < network.return_minst().size(); i++)
			{
				network.forwardPropagation(i);
				network.backwardPropagation(i);
			}
			*/
			
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
			network.forwardPropagation();
		}
		else
		{
			std::cout << "Error: Faild to open a file." << std::endl;
		}
	}
};
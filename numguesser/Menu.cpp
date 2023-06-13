#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "classes.h"
#include "structures.h"

void Menu::start()
{
	std::string input;
	while (true)
	{
		std::cout << "Enter command: ";
		std::getline(std::cin, input);
		std::stringstream ss(input);
		std::vector<std::string> tokens;
		std::string token;
		while (ss >> token) tokens.push_back(token);
		if (tokens.empty()) continue;

		if (tokens[0] == "set") 
		{
			if (tokens.size() == 2) loadWAB(tokens[1]);
			else std::cout << "Invalid number of parameters for 'set' command." << std::endl;
		}
		else if (tokens[0] == "train") 
		{
			if (tokens.size() == 8) train(tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]));
			else std::cout << "Invalid number of parameters for 'train' command." << std::endl;
		}
		else if (tokens[0] == "save") 
		{
			if (tokens.size() == 2) saveWAB(tokens[1]);
			else std::cout << "Invalid number of parameters for 'save' command." << std::endl;
		}
		else if (tokens[0] == "feed") 
		{
			if (tokens.size() == 3) feed(tokens[1], std::stoi(tokens[2]));
			else std::cout << "Invalid number of parameters for 'feed' command." << std::endl;
		}
		else std::cout << "Invalid command." << std::endl;
	}
}

void Menu::loadWAB(const std::string& fileName)
{
	std::cout << "loadWAB start" << std::endl;//temp<<<<<<
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
	std::cout << "try file" << std::endl;//temp<<<<<<
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::cout << "go for hidden" << std::endl;//temp<<<<<<
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
	std::cout << "loadWAB done" << std::endl;//temp<<<<<<
}

void Menu::train(const std::string& fileName, const int& nHiLayerNeurons, const int& batchSize, const int& epochSize, const double& learningRate, const bool& initialize, const int& batchRange)
{
	std::ifstream file(fileName);
	std::string line;
	std::string value;
	int counter=0;
	if(initialize==false) network.initializeWAB(nHiLayerNeurons, 10);
	for (int i = 0; i < epochSize; i++)
	{
		int range = 0;
		if (file.is_open())
		{
			std::cout << ">> epoch No." << i << " START" << std::endl;//temp<<<<<<
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
				network.add_minst(item);
				//std::cout << "> example added" << std::endl;//temp<<<<<<
				if (counter == batchSize)
				{
					//network.initializeWAB(nHiLayerNeurons, 10);
					//std::cout << ">> initialization_done" << std::endl;//temp<<<<<<
					network.forwardPropagation(true);
					//std::cout << ">> forProp_done" << std::endl;//temp<<<<<<
					network.backwardPropagation(learningRate);
					//std::cout << ">> backProp_done" << std::endl;//temp<<<<<<
					network.kill_minst();
					counter = 0;
					if (batchRange >= 0)
						if (range == batchRange) break;
						range++;
				}

				counter++;
			}
			network.epoch();
			file.close();
			std::cout << ">> epoch DONE" << std::endl;//temp<<<<<<
		}
		else
		{
			std::cout << "Error: Faild to open a file." << std::endl;
			break;
		}
	}
}

void Menu::saveWAB(const std::string& fileName)
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

		file.close();
	}
	else std::cout << "Error: Failed to open a file." << std::endl;
}

void Menu::feed(const std::string& fileName, const int& task)
{
	//std::cout << "feed start" << std::endl;//temp<<<<<<
	std::ifstream file(fileName);
	std::string line;
	std::string value;
	
	if (file.is_open())
	{
		int currentLine = 0;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			if (currentLine == task)
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
				network.add_minst(item);
				break;
			}
			currentLine++;
		}
		std::cout << "Example Image:" << std::endl;
		for (int row = 0; row < 28; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				int pixelValue = network.return_minst()[0].pixels[row * 28 + col];
				if (pixelValue > 170) std::cout << "0";
				else if (pixelValue > 85) std::cout << "O";
				else if (pixelValue > 0) std::cout << "o";
				else std::cout << ".";
			}
			std::cout << std::endl;
		}
		network.forwardPropagation(false);
		network.kill_minst();
	}
	else std::cout << "Error: Faild to open a file." << std::endl;
	//std::cout << "feed done" << std::endl;//temp<<<<<<
}
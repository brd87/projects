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
	bool isSet = false;
	while (true)
	{
		std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		std::cout << "Command list\n" << std::endl;
		std::cout << "- Load file with weights and biases:\n\tset [file name]" << std::endl;
		std::cout << "- Train network with chossen data set:\n\ttrain [file name] [number of hidden neurons] [mini-batch size] [number of epochs] [learning rate] [is WAB? 1/0] [data range (-1 for unlimited)]" << std::endl;
		std::cout << "- Save weights and biases into file:\n\tsave [file name]" << std::endl;
		std::cout << "- Display and guess number from test file:\n\tfeed [file name] [number index]" << std::endl;
		std::cout << "- Quit:\n\tq" << std::endl;
		std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
		std::cout << "Enter command: ";
		std::getline(std::cin, input);
		std::stringstream ss(input);
		std::vector<std::string> tokens;
		std::string token;
		while (ss >> token) tokens.push_back(token);
		if (tokens.empty()) continue;

		if (tokens[0] == "set") 
		{
			if (tokens.size() == 2)
			{
				loadWAB(tokens[1]);
				if(network.return_ouLayer().return_Bias().size()!=0) isSet = true;
			}
			else std::cout << "Invalid number of parameters for 'set' command." << std::endl;
		}
		else if (tokens[0] == "train") 
		{
			if (tokens.size() == 8)
			{
				if (!isSet && std::stoi(tokens[6]) == 1) std::cout << "Weights and Biases are not initialized." << std::endl;
				else
				{
					train(tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]), std::stod(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]));
					isSet = true;
				}
			}
			else std::cout << "Invalid number of parameters for 'train' command." << std::endl;\
			
		}
		else if (tokens[0] == "save") 
		{
			if (tokens.size() == 2)
			{
				if (!isSet) std::cout << "Weights and Biases are not initialized." << std::endl;
				else saveWAB(tokens[1]);
			}
			else std::cout << "Invalid number of parameters for 'save' command." << std::endl;
		}
		else if (tokens[0] == "feed") 
		{
			if (tokens.size() == 3)
			{
				if (!isSet) std::cout << "Weights and Biases are not initialized." << std::endl;
				else feed(tokens[1], std::stoi(tokens[2]));
			}
			else std::cout << "Invalid number of parameters for 'feed' command." << std::endl;
		}
		else if(tokens[0] == "q")
		{
			break;
		}
		else std::cout << "Invalid command." << std::endl;
	}
}

void Menu::loadWAB(const std::string& fileName)
{
	DeepLayer holdLayer;
	std::vector<double> holdBias;
	std::vector<std::vector<double>> holdWeights;
	std::ifstream file(fileName);
	std::string line;
	bool isH = false;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line.empty()) continue;
			if (line == "W")
			{
				isH = true;
				holdLayer.modify_Bias(holdBias);
				holdLayer.modify_Weights(holdWeights);
				network.modify_ouLayer(holdLayer);
				holdBias.clear();
				holdWeights.clear();
				continue;
			}
			bool isBias = true;
			std::string value;
			std::vector<double> holdNuronWeights;
			std::stringstream ss(line);

			while (std::getline(ss, value, ','))
			{
				if (!value.empty())
				{
					if (isBias)
					{
						holdBias.push_back(std::stod(value));
						isBias = false;
					}
					else
					{
						holdNuronWeights.push_back(std::stod(value));
					}
				}
			}
			holdWeights.push_back(holdNuronWeights);
		}

		file.close();
		holdLayer.modify_Bias(holdBias);
		holdLayer.modify_Weights(holdWeights);
		network.modify_hiLayer(holdLayer);
		if (network.return_ouLayer().return_Bias().size() != 0)
		{
			std::cout << "Output Layer:" << std::endl;
			std::cout << "  Number of Biases: " << network.return_ouLayer().return_Bias().size() << std::endl;
			std::cout << "  Number of Weight sets: " << network.return_ouLayer().return_Weights().size() << std::endl;
			std::cout << "  Number of Weights per Neuron: " << network.return_ouLayer().return_Weights()[0].size() << std::endl;

			std::cout << "Hidden Layer:" << std::endl;
			std::cout << "  Number of Biases: " << network.return_hiLayer().return_Bias().size() << std::endl;
			std::cout << "  Number of Weight sets: " << network.return_hiLayer().return_Weights().size() << std::endl;
			std::cout << "  Number of Weights per Neuron: " << network.return_hiLayer().return_Weights()[0].size() << std::endl;
		}
		else
		{
			std::cout << "No data loaded from file." << std::endl;
		}
	}
	else
	{
		std::cout << "Error: Failed to open a file." << std::endl;
	}
}

void Menu::train(const std::string& fileName, const int& nHiLayerNeurons, const int& batchSize, const int& epochSize, const double& learningRate, const bool& initialize, const int& batchRange)
{
	std::ifstream file(fileName);
	std::string line;
	std::string value;
	int counter=0;

	if (initialize == false) network.initializeWAB(nHiLayerNeurons, 10);

	if (file.is_open())
	{
		for (int i = 0; i < epochSize; i++)
		{
			int range = 1;
			bool firstBatch = true;
			std::cout << "Epoch No." << i+1 << std::endl;

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
				if (counter == batchSize || (firstBatch && counter==(batchSize-1)))
				{
					network.forwardPropagation(true);
					network.backwardPropagation(learningRate);
					network.kill_minst();
					counter = 0;
					firstBatch = false;
					if (batchRange >= 0)
					{
						if (batchRange <= range)
						{
							file.close();
							file.open(fileName);
							range = 0;
							break;
						}
						range++;
					}
				}

				counter++;
			}

			network.epoch();
		}

		file.close();
	}
	else
	{
		std::cout << "Error: Failed to open the file." << std::endl;
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
}
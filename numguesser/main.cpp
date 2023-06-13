#include <iostream>

#include "classes.h"

int main()
{
	std::cout << "NETWORK" << std::endl;
	Menu Test;
	std::cout << "Here we go" << std::endl;
	//Test.train("mnist_train.csv", 1000, 500, 2, 0.1, 0, 5); //(fileName, nHiLayerNeurons, batchSize, epochSize, LearningRate, inistialize)
	Test.start();
	std::cout << "THAT'S IT, IT'S OVER";
	
	return 0;
}
#include <iostream>

#include "classes.h"

int main()
{
	std::cout << "NETWORK" << std::endl;
	Menu Test;
	std::cout << "Here we go" << std::endl;
	Test.train("mnist_train.csv", 1000, 100, 2, 0); //(fileName, nHiLayerNeurons, batchSize, epochSize)
	Test.start();
	std::cout << "THAT'S IT, IT'S OVER";
	
	return 0;
}
#include <iostream>

#include "classes.h"

int main()
{
	std::cout << "NETWORK" << std::endl;
	Menu Test;
	std::cout << "Here we go" << std::endl;
	Test.train("mnist_train.csv", 1000, 10, 2);
	std::cout << "File loaded";
	Test.start();
	return 0;
}
#include <iostream>

#include "classes.h"

int main()
{
	std::cout << "NETWORK";
	Menu Test;
	Test.train("mnist_train.csv", 1000);
	std::cout << "File loaded";
	return 0;
}
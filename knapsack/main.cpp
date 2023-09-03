#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <map>
#include <deque>

#include "structures.h"
#include "functions.h"

int main(int ile, char* params[])
{
//    for (int i = 0; i < ile; i++)
//        std::cout << "[" << i << "]: " << params[i] << std::endl;


//    std::map<std::string, std::string> parametry = { {"-i", "input.txt"}, {"-o", "output.txt"}, {"-c", "20"}, {"-g", "10"}, {"-n", "20"} }; //emergency parameters if console input would not work
    std::map<std::string, std::string> parametry = paramcheck(ile, params);
    if (parametry.count("error") || parametry["-i"] == "")
    {
        std::cout << "Error: Incorrect parameters" << std::endl;
        return 0;
    }
    std::deque<item> items = dataread(parametry.at("-i"));

    if (items.size() == 0)
    {
        std::cout << "Error: Encountered a problem during openning a file" << std::endl;
        return 0;
    }
    if (items[0].name == "error")
    {
        std::cout << "Error: Inputed data was incorrect!" << std::endl;
        return 0;
    }
//    std::cout << "Ping-" << std::endl;
    genetic(items, std::stod(parametry.at("-n")), std::stod(parametry.at("-c")), std::stod(parametry.at("-g")), parametry.at("-o"));
//    std::cout << "-Pong (finished)" << std::endl;

    return 0;
}
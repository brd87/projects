/**  @file */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

#include "structures.h" 


/**
 * @brief Parameter checker
 *
 * Checks the parameters passed to the program and stores them in a map, where the keys are the names of the parameters and the map values are their values.
 *
 * @param ile The number of parameters passed to the program
 * @param param The array of parameters passed to the program
 *
 * @return A map containing the parameters and their values
 */
std::map<std::string, std::string> paramcheck(int ile, char* param[]);

/**
 * @brief Data reader
 *
 * This function reads and checks the data from a file and stores it in a deque of struct items.
 *
 * @param filename The name of the file containing the data
 *
 * @return A deque of struct items
 */
std::deque<item> dataread(const std::string& filename);

/**
 * @brief Random number generator
 *
 * This function generates a random integer in the range [0, a].
 *
 * @param limit The upper bound of the range
 *
 * @return A random integer
 */
int randomint(const int& limit);

/**
 * @brief Knapsack generator
 *
 * This function generates a struct variable plecak given a set of items and a capacity.
 *
 * @param items The set of items
 * @param capacity The capacity of the knapsack
 *
 * @return A knapsack
 */
plecak generate_knapsack(const std::deque<item>& items, const double& capacity);

/**
 * @brief First generation generator
 *
 * This function generates the first generation of knapsacks which is made out of structure populacja.
 *
 * @param items The set of items
 * @param count The number of knapsacks in the generation
 * @param capacity The capacity of each knapsack
 *
 * @return The first generation of knapsacks
 */
populacja generatefirstgen(const std::deque<item>& items, const double& count, const double& capacity);

/**
 * @brief Value-Weight calculator
 *
 * This function calculates the value and weight of each knapsack in a generation.
 *
 * @param items The set of items
 * @param generation The current population of knapsacks
 *
 * @return The updated generation of knapsacks with their values and weights calculated
 */
populacja VWcalcualator(const std::deque<item>& items, populacja& generation);

/**
 * @brief Crossing operation
 * 
 * Creates new knapsacks by choosing and merging two individuals taken from generation.
 *
 * @param generation The current population of knapsacks
 * @param items The set of items
 *
 * @return New population based on previus one
 */
populacja crossing(const std::deque<item>& items, const populacja& generation);

/**
 * @brief Select operation
 * 
 * Selects the best individuals from the current generation based on their fitness value.
 *
 * @param generation The current population of knapsacks
 * @param capacity The capacity of each knapsack
 *
 * @return New population based on previus one
 */
populacja selection(const populacja& generation, const double& count, const double& capacity);

/**
 * @brief Best solution calculator
 *
 * Finds best knapsack by comparing all candidates in generation.
 *
 * @param generation The current population of knapsacks
 * @param capacity The capacity of each knapsack
 *
 * @return The best solution
 */
plecak topplecak(const populacja& generation, const double& capacity);

/**
 * @brief Data output operation
 * 
 * Writes the best solution of a generation to the text file with the information about items, total value and weight of an knapsack.
 *
 * @param generation The current population of knapsacks
 * @param output The name of the output file
 * @param gen The current generation number
 * @param items The set of items
 * @param capacity The capacity of each knapsack
 * @param file The output file stream
 */
void datawrite(const populacja& generation, const double& gen, const std::deque<item>& items, const double& capacity, std::ofstream& file);

/**
 * @brief Man genetic function
 * 
 * Generates best solution for knapsack problem by combining other sub-functions.
 *
 * @param items The set of items
 * @param count The number of knapsacks in the generation
 * @param capacity The capacity of each knapsack
 * @param gennumber The number of generations to run the algorithm for
 * @param output The name of the output file
 */
void genetic(const std::deque<item>& items, const double& count, const double& capacity, const double& gennumber, const std::string& output);

#endif
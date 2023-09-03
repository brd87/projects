/**  @file */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

/**
 * @struct item
 * @brief Represents an item in the backpack problem
 *
 * @param name Name of the item
 * @param weight Weight of the item
 * @param value Value of the item
 * @param numer Number of the item
 */
struct item
{
    std::string name;
    double  weight;
    double  value;
    int numer;
};

/**
 * @struct plecak
 * @brief Represents a backpack in the backpack problem
 *
 * @param przedmioty Vector of booleans representing whether an item is in the backpack or not
 * @param waga Total weight of the items in the backpack
 * @param wartosc Total value of the items in the backpack
 */
struct plecak
{
    std::vector<bool> przedmioty;
    double waga;
    double wartosc;
};

/**
 * @struct populacja
 * @brief Represents a population in the backpack problem
 *
 * @param plecaki Vector of backpacks in the population
 */
struct populacja
{
    std::vector<plecak> plecaki;
};



#endif
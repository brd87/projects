#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <numeric>
#include <deque>

#include "functions.h"
#include "structures.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
std::map<std::string, std::string> paramcheck(int ile, char* param[])
{
    std::map<std::string, std::string> parametry = { {"-i", ""}, {"-o", ""}, {"-c", ""}, {"-g", ""}, {"-n", ""} };
    for (int i = 1; i < ile; i += 2)
    {
        if (parametry.count(param[i]))
            parametry[param[i]] = param[i + 1];
        else
            return { {"error",""} };
    }

    return parametry;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
std::deque<item> dataread(const std::string& filename)
{
    std::ifstream file(filename);
    std::deque<item> items;

    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            item i;
            std::stringstream ss(line);
            if (ss >> i.name >> i.weight >> i.value)
                items.push_back(i);
            else
            {
                items.push_front({ "error", 0, 0 ,0 });
                break;
            }
        }
    }
    file.close();
    for (int i = 0; i < items.size(); i++)
    {
        items[i].numer = i;
    }
    return items;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
int randomint(const int& limit)
{
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> value(0, limit);
    return value(engine);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
plecak generate_knapsack(const std::deque<item>& items, const double& capacity)
{
    plecak candidate;
    int holder;
    std::vector<int> numery(items.size());
    std::iota(numery.begin(), numery.end(), 0);
    candidate = { std::vector<bool>(items.size(), false), 0, 0 };

    while (true)
    {
        holder = numery[randomint(numery.size() - 1)];
        for (int address = 0; address < items.size(); address++)
        {
            if (items[address].numer == holder)
            {
                holder = address;
                break;
            }
        }

        if (candidate.waga + items[holder].weight > capacity) break;
        if (candidate.przedmioty[holder] == 1) continue;

        candidate.przedmioty[holder] = 1;
        candidate.waga += items[holder].weight;
        candidate.wartosc += items[holder].value;
        std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
        std::shuffle(numery.begin(), numery.end(), engine);
    }

    return candidate;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
populacja generatefirstgen(const std::deque<item>& items, const double& count, const double& capacity)
{
//    std::cout << "firstgen inside" << std::endl;//<<<<<<<<<<
    populacja generation;

    for (int i = 0; i < count; i++)
        generation.plecaki.push_back(generate_knapsack(items, capacity));

/*
    for (auto i : generation.plecaki)//<<<<<<<<<<
    {
        std::cout << "elements: {";
        for (auto n : i.przedmioty)
        {
            std::cout << " " << n << " ";
        }
        std::cout << "} Wartosc: " << i.wartosc << " Waga: " << i.waga << std::endl;
    }//<<<<<<<<<<
*/

    return generation;

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
populacja VWcalcualator(const std::deque<item>& items, populacja& generation)
{
    double waga;
    double wartosc;
    for (int i = 0; i < generation.plecaki.size(); i++)
    {
        waga = 0;
        wartosc = 0;
        for (int n = 0; n < items.size(); n++)
        {
            if (generation.plecaki[i].przedmioty[n] == 1)
            {
                waga += items[n].weight;
                wartosc += items[n].value;
            }
        }
        generation.plecaki[i].waga = waga;
        generation.plecaki[i].wartosc = wartosc;
    }
    return generation;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
populacja crossing(const std::deque<item>& items, const populacja& generation)
{   
    populacja fatgeneration;
    int crosspoint;
    std::vector<bool> X;
    std::vector<bool> Y;
    std::vector<plecak> set;
    for (auto i : generation.plecaki)
    {
        X = i.przedmioty;
        Y = generation.plecaki[randomint(generation.plecaki.size()-1)].przedmioty;
        crosspoint = randomint(items.size()-1);
        set = { {},{} };
        for (int cell = 0; cell < items.size(); cell++)
        {

            if (cell == crosspoint) std::swap(Y, X);

            set[0].przedmioty.push_back(Y[cell]);
            set[1].przedmioty.push_back(X[cell]);
        }
        fatgeneration.plecaki.push_back(set[0]);
        fatgeneration.plecaki.push_back(set[1]);
    }

    fatgeneration = VWcalcualator(items, fatgeneration);
    return fatgeneration;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
populacja selection(const populacja& generation, const double& count, const double& capacity)
{
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> rozklad(0, 1);
    populacja postgeneration;
    std::vector<double> ruletka;
    double sum=0;
    for (int i = 0; i < generation.plecaki.size(); i++)
        sum += generation.plecaki[i].wartosc;
    plecak top = topplecak(generation, capacity);
    
    ruletka.push_back(generation.plecaki[0].wartosc/sum);
    for (int i = 1; i < generation.plecaki.size(); i++)
    {
        ruletka.push_back(generation.plecaki[i].wartosc / sum + ruletka[i-1]);
        if (generation.plecaki[i].waga == 0 || generation.plecaki[i].waga > capacity) ruletka[i] /= 2;
        if (top.wartosc == generation.plecaki[i].wartosc) ruletka[i] *= 2;
    }
        

    while (postgeneration.plecaki.size()<count)
    {
        for (int i = 0; i < ruletka.size(); i++)
        {
            if (rozklad(engine) <= ruletka[i])
            {
                postgeneration.plecaki.push_back(generation.plecaki[i]);
                break;
            }
        }
    }
/*
    for (auto i : postgeneration.plecaki)//<<<<<<<<<<
    {
        std::cout << "elements: {";
        for (auto n : i.przedmioty)
        {
            std::cout << " " << n << " ";
        }
        std::cout << "} Wartosc: " << i.wartosc << " Waga: " << i.waga << std::endl;
    }//<<<<<<<<<<
*/
    return postgeneration;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
plecak topplecak(const populacja& generation, const double& capacity)
{
    plecak top;
    top.wartosc = 0;
    for (auto i : generation.plecaki)
    {
        if (i.wartosc > top.wartosc && i.waga <= capacity)
            top = i;
    }
    return top;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void datawrite(const populacja& generation, const double& gen, const std::deque<item>& items, const double& capacity, std::ofstream& file)
{
    plecak top = topplecak(generation, capacity);
    if (top.wartosc == 0)
    {
        file << "Generation " << gen << "- This generation has no proper best solution\n";
        return;
    }
    file << "Generation " << gen << ", weight " << top.waga << ", value " << top.wartosc << ": \n";
    for (int i = 0; i < top.przedmioty.size(); i++)
    {
        if (top.przedmioty[i] == 1)
            file << items[i].name << "\t" << items[i].weight << "\t" << items[i].value << "\n";
    }
    file << "\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void genetic(const std::deque<item>& items, const double& count, const double& capacity, const double& gennumber, const std::string& output)
{   
    std::ofstream file(output);
//    std::cout << "first gen: start" << std::endl;//<<<<<<<<<<
    populacja generation = generatefirstgen(items, count, capacity);
//    std::cout << "first gen: over\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;//<<<<<<<<<<
    for (int gen = 1; gen <= gennumber; gen++)
    {
//        std::cout << "operating on gen:" << gen << std::endl;//<<<<<<<<<<
        generation = selection(crossing(items, generation), count, capacity);
//        std::cout << "datawrite\n//////////////////////////////////////////////////////////////////////////////" << std::endl;//<<<<<<<<<<
        datawrite(generation, gen, items, capacity, file);
    }
    file.close();
}
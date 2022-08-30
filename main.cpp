#include <iostream>
#include <fstream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "GA/Population.h"
#include "GA/types.h"


int main(int argc, char **argv) 
{   
/*
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, 100);

    std::cout << dist(mt) << std::endl;

    return 0;
*/


    Population population;
    population.createInitialPopulation(6,10);
    population.show();

    NewGenParams newGenParams;
    newGenParams.selectionType = SELECTION_TYPE::ESTOCASTIC;
    newGenParams.crossoverType = CROSSOVER_TYPE::UNIFORM;
    newGenParams.mutationType  = MUTATION_TYPE::INSERTION;

    population.generateNewPopulation(newGenParams);
    //population.show();
    
    return 0;
}
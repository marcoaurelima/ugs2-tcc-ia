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
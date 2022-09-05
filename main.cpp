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

// testando commit

int main(int argc, char **argv) 
{   
    Population population;
    population.createInitialPopulation(8,10);
    population.show();

    NewGenParams newGenParams;
    newGenParams.selectionType = SELECTION_TYPE::ROULLETE;
    newGenParams.crossoverType = CROSSOVER_TYPE::SINGLE_POINT;
    newGenParams.mutationType  = MUTATION_TYPE::INSERTION;

    population.generateNewPopulation(newGenParams);


    return 0;
}
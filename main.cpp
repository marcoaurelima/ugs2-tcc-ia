#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "Population.h"
#include "types.h"



int main(int argc, char **argv) 
{
    Population population;
    population.createInitialPopulation(3,36);
    population.show();

    NewGenParams newGenParams;
    newGenParams.crossoverType = CROSSOVER_TYPE::MULTI_POINT;
    newGenParams.mutationType  = MUTATION_TYPE::INSERTION;
    newGenParams.selectionType = SELECTION_TYPE::FITNESS;

    population.generateNewPopulation(newGenParams);

    return 0;
}
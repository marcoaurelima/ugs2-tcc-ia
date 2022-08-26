#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <initializer_list>
#include "Population.h"
#include "types.h"


int main(int argc, char **argv) 
{
    Population population;
    population.createInitialPopulation(3,36);
    population.show();

    NewGenParams n;
    n.crossoverType = CROSSOVER_TYPE::MULTI_POINT;
    n.mutationType  = MUTATION_TYPE::INSERTION;
    n.selectionType = SELECTION_TYPE::FITNESS;

    population.generateNewPopulation(n);

    return 0;
}
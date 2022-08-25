#include <iostream>
#include <array>

#include "Population.h"

#include "types.h"

int main(int argc, char **argv) 
{
    Population population;
    population.createInitialPopulation(3,36);
    population.show();

    NewGenInfo n;
    n.crossoverType = CROSSOVER_TYPE::MULTI_POINT;
    n.mutationType = MUTATION_TYPE::INSERTION;
    n.selectionType = SELECTION_TYPE::FITNESS;

    return 0;
}
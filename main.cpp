#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "Population.h"
#include "types.h"

void mutationInsertion(std::vector<float> chromosome)
{
    size_t chromosomeSize = chromosome.size();

    srand((unsigned int)time(NULL));
    unsigned index1 = 0, index2 = 0;
    while (index1 == index2) 
    {
        index1 = (rand() % chromosomeSize*100)/100;
        index2 = (rand() % chromosomeSize*100)/100;
    }
    
    // Ordenar indices; index1 deve conter menor valor dos dois

    if(index1 > index2)
    {
        unsigned temp = index1;
        index1 = index2;
        index2 = temp;
    }

    std::cout << index1 << " " << index2 << " " <<  "\n"; 




}

int main(int argc, char **argv) 
{

    mutationInsertion(std::vector<float>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28});

    return 0;
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
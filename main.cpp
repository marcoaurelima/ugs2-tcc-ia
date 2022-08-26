#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "Population.h"
#include "types.h"

std::vector<float> mutationInsertion(std::vector<float> chromosome)
{
    size_t chromosomeSize = chromosome.size();

    srand((unsigned int)time(NULL));
    unsigned index1 = 0, index2 = 0;
    while (index1 == index2) 
    {
        index1 = (rand() % chromosomeSize*100)/100;
        index2 = (rand() % chromosomeSize*100)/100;
    }
    
    // Ordenar indices - index1 deve conter menor valor dos dois

    if(index1 > index2)
    {
        unsigned temp = index1;
        index1 = index2;
        index2 = temp;
    }
    
    std::vector<float> mutation {};

    // Salvar valor de (index1) para variavel (auxiliar)
    // Copiar para mutation os valores até (index2)-1, pulando o valor de (index1)
    // Inserir valor de (auxiliar) em (index2)-1
    // Copiar para mutation os valores restantes a partir de (index2)

    float aux = chromosome[index1];
    for (size_t i = 0; i < index2; i++)
    {
        if(i == index1){ continue; }
        mutation.push_back(chromosome[i]);
    }

    mutation.push_back(aux);

    for (size_t i = index2; i < chromosomeSize; i++)
    {
        mutation.push_back(chromosome[i]);
    }

    return mutation; 

}

int main(int argc, char **argv) 
{

    auto res =mutationInsertion(std::vector<float>{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28});

    for(auto& i : res)
    {
        std::cout<<i<<" ";
    }


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
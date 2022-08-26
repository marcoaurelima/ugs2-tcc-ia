#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "Population.h"
#include "types.h"


// parent1 / parent2:       Cromossomos dos pais
// taxParent1 / taxParent2: taxa em porcentagem da participação dos respectivos pais no cruzamento. 
std::vector<float> crossoverUniform(std::vector<float> parent1, std::vector<float> parent2, unsigned taxParent1, unsigned taxParent2)
{
    if(parent1.size() != parent2.size())
    {
        std::cerr << "Error: parent1 and parent2 must have the same size." << std::endl;
        return std::vector<float>();
    }

    if(taxParent1 + taxParent2 != 100)
    {
        std::cerr << "Error: Invalid number of taxParent1." << std::endl;
        return std::vector<float>();
    }

    size_t chromossomeSize = (parent1.size() + parent1.size()) / 2;
    unsigned parent1size = (chromossomeSize * taxParent1) / 100;
    unsigned parent2size = chromossomeSize - parent1size;

    // Produzir a mascara binária;
    // Será gerado trues de acordo com a porcentagem do pai 1;
    // Será gerado falses com a quantidade que faltar para completar a mascara;

    std::vector<bool> mask {};
    for (size_t i = 0; i < parent1size; i++) { mask.push_back(true); }
    for (size_t i = 0; i < parent2size; i++) { mask.push_back(false); }
    
    // Embaralhar mascara de forma aleatória
    
    std::random_device randDevice {};
    std::default_random_engine randEngine{randDevice()};
    std::shuffle(std::begin(mask), std::end(mask), randEngine);

    // Efetuar cruzamento a partir da mascara

    std::vector<float> child {};
    for (size_t i = 0; i < mask.size(); i++)
    {
        if(mask[i] == true) {
            child.push_back(parent1[i]);
        } 
        else {  
            child.push_back(parent2[i]);
        }
    }

    return child;
}


int main(int argc, char **argv) 
{
    std::vector<float> pai1 {0,1,2,3,4,5,6,7,8,9};
    std::vector<float> pai2 {10,11,12,13,14,15,16,17,18,19};

    auto res = crossoverUniform(pai1, pai2, 50, 50); 
    
    for(auto& i : res)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
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
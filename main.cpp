#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "Population.h"
#include "types.h"

std::vector<char> cruzamentouniforme(std::vector<char> parent1, std::vector<char> parent2, unsigned taxParent1, unsigned taxParent2)
{
    size_t chromossomeSize = (parent1.size() + parent1.size()) / 2;
    unsigned parent1size = (chromossomeSize * taxParent1) / 100;
    unsigned parent2size = chromossomeSize - parent1size;

    std::cout << "parent1size: " << parent1size << " parent2size: " << parent2size << std::endl;

    // Produzir a mascara binária;
    // Será gerado trues de acordo com a porcentagem do pai 1;
    // Será gerado falses com a quantidade que faltar para completar a mascara;

    std::vector<bool> mask {};
    for (size_t i = 0; i < parent1size; i++) { mask.push_back(true); }
    for (size_t i = 0; i < parent2size; i++) { mask.push_back(false); }
    
    for (size_t i = 0; i < mask.size(); i++) 
    {
        std::cout << mask[i];
    }
    puts("");
    
    std::random_device randDevice {};
    std::default_random_engine randEngine{randDevice()};
    std::shuffle(std::begin(mask), std::end(mask), randEngine);

    for (size_t i = 0; i < mask.size(); i++) 
    {
        std::cout << mask[i];
    }
    puts("");

    std::vector<char> filho {};
    for (size_t i = 0; i < mask.size(); i++)
    {
        if(mask[i] == true)
        {
            filho.push_back(parent1[i]);
        } 
        else {  
            filho.push_back(parent2[i]);
        }
    }

    return filho;

}


int main(int argc, char **argv) 
{
    std::vector<char> pai1 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    std::vector<char> pai2 {'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};

    auto res = cruzamentouniforme(pai1, pai2, 50, 50); 
    
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
#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <initializer_list>
#include "Population.h"
#include "types.h"

void cruzamentouniforme(std::vector<char> parent1, std::vector<char> parent2, unsigned taxParent1, unsigned taxParent2)
{
    size_t chromossomeSize = (parent1.size() + parent1.size()) / 2;
    // Produzir a mascara;
    // Será gerado '0's de acordo com a porcentagem do pai 1;
    // Será gerado '1's com a quantidade que faltar para completar a mascara;
    
    unsigned parent1size = (chromossomeSize * taxParent1) / 100;
    unsigned parent2size = chromossomeSize - parent1size;

    std::cout << "parent1size: " << parent1size << " parent2size: " << parent2size << std::endl;

    
    /*

    std::vector<bool> mask {};
    for (unsigned i = 0; i < parent1.size(); ++i)

    // Todos os vetores tem que ter tamanhos iguais verificar isso no algortmo.

    std::vector<char> filho {};
    for (size_t i = 0; i < mask.size(); i++)
    {
        if(mask[i] == 0)
        {
            filho.push_back(parent1[i]);
        } 
        else {  
            filho.push_back(parent2[i]);
        }
    }
    
    for (auto &i : filho)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    */

}


int main(int argc, char **argv) 
{

    std::vector<char> pai1 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    std::vector<char> pai2 {'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};

    cruzamentouniforme(pai1, pai2, 30, 70); return 0;

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
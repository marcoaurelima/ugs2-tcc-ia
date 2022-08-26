#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <initializer_list>

#include "Population.h"

#include "types.h"




void selecaoestocastica()
{
    std::vector<float> fitnessCromossomos {5,3,2,1};
    int qtd_agulhas = 4;
    int giro = 20;
    float soma_fitness = 5.0 + 3.0 + 2.0 + 1.0;

    unsigned p1 = (5.0 / soma_fitness) * 100;
    unsigned p2 = (3.0 / soma_fitness) * 100;
    unsigned p3 = (2.0 / soma_fitness) * 100;
    unsigned p4 = (1.0 / soma_fitness) * 100;

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << p4 << std::endl;

    std::deque<float> roleta {};

    for (size_t i = 0; i < p1; i++)
    {
        roleta.push_back(1);
    }
    
    for (size_t i = 0; i < p2; i++)
    {
        roleta.push_back(2);
    }
    
    for (size_t i = 0; i < p3; i++)
    {
        roleta.push_back(3);
    }

    for (size_t i = 0; i < p4; i++)
    {
        roleta.push_back(3);
    }
    

    std::cout << "total: " << roleta.size() << std::endl;

    for (auto &i : roleta)
    {
        std::cout << i;
    }
    puts("");
    

    /// girar a roleta
    for (size_t i = 0; i < giro; i++)
    {
        roleta.push_back(roleta[i]);
        roleta.pop_front();
    }
    
    for (auto &i : roleta)
    {
        std::cout << i;
    }
    puts("");
    

    std::set<int> cromossomosSelecionados;
    //selecionar novos valores na rolera girada
    for (size_t i = 0; i < qtd_agulhas; i++)
    {
        int offset = ((100 / qtd_agulhas) * i) + ((100 / qtd_agulhas)/2);

        cromossomosSelecionados.insert(offset);
    }
    
    std::cout << "--------------------------------\n";
    for (auto &i : cromossomosSelecionados)
    {
        std::cout << i << " ";
    }
    puts("");

    std::cout << "Cromossomos selecionados: " << std::endl;
    for (auto &i : cromossomosSelecionados)
    {
        std::cout << roleta[i] << " ";
    }

}

int main(int argc, char **argv) 
{
    selecaoestocastica();

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
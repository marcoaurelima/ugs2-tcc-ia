#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <initializer_list>
#include "Population.h"
#include "types.h"

#define DEBUG

// fitness: vetor com todos os fitness que estarao na roleta
// qtdNidles: quantidade de agulhas na roleta
// spin: giro da roleta; porcentagem do giro 1% - 99%
std::set<float> selecaoestocastica(std::vector<float> fitness, unsigned qtdNidles, unsigned spin)
{
    float fitnessSum = 0;
    for (auto &i : fitness) {  fitnessSum += i; }
    
    // Produzir um vetor de aprox. de 100 posições (valores float as vezes somam 99% no total),
    // onde terão vários blocos de valores repetidos representando as fatias da roleta.
    // cada bloco conterá o indice do cromossomo. Ex.: 001111222
    // No caso acima, o fitness na posição 2 tem uma fatia maior, enquanto o 0 tem a menor.

    std::vector<unsigned> percents;
    for (unsigned i = 0; i < fitness.size(); i++)
    {
        unsigned value = (fitness[i] / fitnessSum) * 100;
        percents.push_back(value);
    }
    
    // Preencher a roleta com blocos de valores

    std::deque<float> roleta {};
    for(unsigned int i = 0; i < percents.size(); i++)
    {
        for (unsigned j = 0; j < percents[i]; j++)
        {
            roleta.push_back(i);
        }  
    }
    
    #ifdef DEBUG
    for (auto &i : roleta) { std::cout << i; }
    puts("");
    #endif

    /// girar a roleta

    for (unsigned i = 0; i < spin; i++) { roleta.push_back(roleta[i]); }
    for (unsigned i = 0; i < spin; i++) { roleta.pop_front(); }
    
    #ifdef DEBUG
    for (auto &i : roleta) { std::cout << i; }
    puts("");
    #endif

    // Calcular indices das agulhas

    std::vector<unsigned> indexNidles {};
    for (size_t i = 0; i < qtdNidles; i++)
    {
        int index = ((100 / qtdNidles) * i) + ((100 / qtdNidles)/2);
        indexNidles.push_back(index);
    }

    #ifdef DEBUG
    for (auto &i : indexNidles) { std::cout << i << " "; }
    puts("");
    #endif

    // Efetuar seleção com base no indice das agulhas

    std::set<float> selection {};
    for (unsigned& i : indexNidles)
    {
        selection.insert(roleta[i]);
    }

    #ifdef DEBUG
    std::cout << "Selection: " << std::endl;
    for (auto &i : selection) { std::cout << i << " "; }
    puts("");
    #endif

    return selection;

}


int main(int argc, char **argv) 
{
    selecaoestocastica(std::vector<float>{1,2,7,9}, 4, 20);

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
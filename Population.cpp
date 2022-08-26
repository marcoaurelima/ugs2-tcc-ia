#include "Population.h"

Population::Population() { }

Population::~Population() { }

float getRandomFloat()
{
    return static_cast<float>((rand()%10000)) / 1000;
}

void Population::createInitialPopulation(const unsigned POPULATION_SIZE, const unsigned CHROMOSSOME_SIZE)
{
    for (size_t i = 0; i < POPULATION_SIZE; i++)
    {
        Chromosome c;
        for (size_t j = 0; j < CHROMOSSOME_SIZE; j++)
        {
            float randFloat = getRandomFloat();
            c.setGene(randFloat);
        }
        c.setRandomFitness();
        chromosomes.push_back(c);
    }   
}

void Population::show()
{
    for(auto& c : chromosomes)
    {
        c.show();
    }
}

void Population::generateNewPopulation(NewGenParams newGenParams)
{
    /// seleção ///
    switch (newGenParams.selectionType)
    {
    case SELECTION_TYPE::FITNESS:
        std::cout << "Seleção FITNESS" << std::endl;
        break;
    case SELECTION_TYPE::TOURNAMENT:
        std::cout << "Seleção TOURNAMENT" << std::endl;
        break;
    case SELECTION_TYPE::ROULLETE:
        std::cout << "Seleção ROULLETE" << std::endl;
        break;
    case SELECTION_TYPE::ESTOCASTIC:
        /* code */
        break;
    
    default:
        break;
    }

    /// cruzamento ///
    switch (newGenParams.crossoverType)
    {
    case CROSSOVER_TYPE::SINGLE_POINT:
        std::cout << "crossover SINGLE_POINT" << std::endl;
        break;
    case CROSSOVER_TYPE::MULTI_POINT:
        std::cout << "crossover MULTI_POINT" << std::endl;
        break;
    case CROSSOVER_TYPE::UNIFORM:
        std::cout << "crossover UNIFORM" << std::endl;
        break;
    
    default:
        break;
    }

    /// cruzamento ///
    switch (newGenParams.mutationType)
    {
    case MUTATION_TYPE::INSERTION:
        std::cout << "mutation INSERTION" << std::endl;
        break;
    case MUTATION_TYPE::INVERSION:
        std::cout << "mutation INSERTION" << std::endl;
        break;
    case MUTATION_TYPE::UNIFORM:
        std::cout << "mutation UNIFORM" << std::endl;
        break;
    
    default:
        break;
    }
}


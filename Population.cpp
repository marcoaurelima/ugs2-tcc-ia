#include "Population.h"

Population::Population()
{

}

Population::~Population()
{

}

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
    
}


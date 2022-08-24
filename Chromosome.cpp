#include "Chromosome.h"

Chromosome::Chromosome(const unsigned SIZE)
{
    values = std::vector<float>(SIZE);
}

void Chromosome::show()
{
    std::cout << "Size: " << values.size() << std::endl;
    for(auto i : values)
    {
        std::cout << "[" << i << "] ";
    }
    std::cout << std::endl;
}

void Chromosome::setFitness(float fitness)
{
    this->fitness = fitness;
}

float Chromosome::getFitness()
{
    return fitness;
}
#include "Chromosome.h"

Chromosome::Chromosome(const std::initializer_list<float> valuesList)
{
    for (auto &i : valuesList)
    {
        values.push_back(i);
    }
}

void Chromosome::show()
{
    std::cout << "Size: " << values.size() << std::endl;
    for (auto i : values)
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
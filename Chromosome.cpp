#include "Chromosome.h"

Chromosome::Chromosome()
{

}

Chromosome::Chromosome(const std::initializer_list<float> valuesList)
{
    for (auto &i : valuesList)
    {
        genes.push_back(i);
    }
}

void Chromosome::show()
{
    std::cout << "Size: " << genes.size() << std::endl;
    for (auto i : genes)
    {
        std::cout << "[" << i << "|" << fitness << "]\t";
    }
    std::cout << std::endl << std::endl;
}

void Chromosome::setFitness(float fitness)
{
    this->fitness = fitness;
}

float Chromosome::getFitness()
{
    return fitness;
}

void Chromosome::setGene(float value)
{
    genes.push_back(value);
}
 
float Chromosome::getGene(const unsigned index)
{
    return genes[index];
}

void Chromosome::setRandomFitness()
{
    fitness = rand() % 99;
}

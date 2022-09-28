#include "GA/Chromosome.h"

Chromosome::Chromosome() {}


Chromosome::Chromosome(const std::initializer_list<float> valuesList)
{
    for (auto &i : valuesList)
    {
        genes.push_back(i);
    }
}


Chromosome::Chromosome(const std::vector<float>& valuesList)
{
    for (auto &i : valuesList)
    {
        genes.push_back(i);
    }
}


void Chromosome::show() const
{
    std::cout << "Size: " << genes.size() << std::endl;
    for (auto i : genes)
    {
        std::cout << std::setprecision(3) << std::fixed;
        std::cout << "[" << i << "|";
        std::cout << fitness << "]\t";
    }
    std::cout << std::endl << std::endl;
}


void Chromosome::setFitness(unsigned fitness)
{
    this->fitness = fitness;
    fitnessWasDefined = true;
}


unsigned Chromosome::getFitness() const
{
    return fitness;
}


void Chromosome::setGene(float value)
{
    genes.push_back(value);
}
 

float Chromosome::getGene(const unsigned index) const
{
    return genes[index];
}


void Chromosome::setRandomFitness()
{
    fitness = rand() % 99;
    fitnessWasDefined = true;
}


std::vector<float> Chromosome::getAllGenes() const
{
    return genes;
}


void Chromosome::setAllGenes(const std::vector<float>& genes)
{
    this->genes.clear();
    this->genes = genes;
}


size_t Chromosome::getSize() const
{
    return genes.size();
}

void Chromosome::changeGene(unsigned index, float value)
{
    genes[index] = value;
}

bool Chromosome::haveFitness() const
{
    return fitnessWasDefined;
}
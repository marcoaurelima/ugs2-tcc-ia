#include "Chromosome.h"

Chromosome::Chromosome(const unsigned SIZE)
{
    values = std::vector<float>(SIZE);

    for(auto i : values)
    {
        std::cout << i << std::endl;
    }
}

Chromosome::~Chromosome()
{

}
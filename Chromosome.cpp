#include "Chromosome.h"

Chromosome::Chromosome(const unsigned SIZE)
{
    values = std::vector<float>(SIZE);

   
}

Chromosome::~Chromosome()
{

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
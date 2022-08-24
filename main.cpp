#include <iostream>
#include <array>

#include "Chromosome.h"

int main(int argc, char **argv) 
{
    Chromosome c(5);
    c.show();
    std::cout << c.getFitness() << std::endl;
    c.setFitness(55);
    std::cout << c.getFitness() << std::endl;
    
    return 0;
}
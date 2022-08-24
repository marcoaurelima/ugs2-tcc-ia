#include <iostream>
#include <array>

#include "Population.h"

int main(int argc, char **argv) 
{
    Population population;
    population.createInitialPopulation(3,10);
    population.show();

    return 0;
}
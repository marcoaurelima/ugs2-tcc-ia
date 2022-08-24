#include <iostream>
#include <array>

#include "Population.h"

int main(int argc, char **argv) 
{
    Population p;
    p.createInitialPopulation(3,10);
    p.show();

    return 0;
}
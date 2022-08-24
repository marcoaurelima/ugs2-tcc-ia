#ifndef POPULATION_H
#define POPULATION_H

#pragma once
#include <vector>
#include "Chromosome.h"

class Population
{
public:
    Population();
    ~Population();

    void createInitialPopulation(const unsigned POPULATION_SIZE);

private:
    std::vector<Chromosome> chromosomes;
};

#endif
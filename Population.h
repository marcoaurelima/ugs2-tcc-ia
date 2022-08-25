#ifndef POPULATION_H
#define POPULATION_H

#pragma once
#include <vector>
#include "Chromosome.h"
#include "types.h"

class Population
{
public:
    Population();
    ~Population();

    void createInitialPopulation(const unsigned POPULATION_SIZE, const unsigned CHROMOSSOME_SIZE);
    void show();

    void generateNewPopulation(NewGenInfo newGenInfo );

private:
    std::vector<Chromosome> chromosomes;
};

#endif
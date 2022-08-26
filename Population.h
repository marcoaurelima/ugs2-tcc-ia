#ifndef POPULATION_H
#define POPULATION_H

#pragma once
#include <vector>
#include <set>
#include <deque>
#include "Chromosome.h"
#include "types.h"

class Population
{
public:
    Population();
    ~Population();

    void createInitialPopulation(const unsigned POPULATION_SIZE, const unsigned CHROMOSSOME_SIZE);
    void show();

    void generateNewPopulation(NewGenParams newGenParams);

private:
    std::vector<Chromosome> chromosomes;

    std::set<float> selectionEstocastic(std::vector<float> fitness, unsigned qtdNidles, unsigned spin);
};

#endif
#ifndef POPULATION_H
#define POPULATION_H

#pragma once
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <random>
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

    std::vector<float> crossoverUniform(std::vector<float> parent1, std::vector<float> parent2, unsigned taxParent1, unsigned taxParent2);


};

#endif
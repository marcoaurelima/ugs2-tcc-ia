#ifndef POPULATION_H
#define POPULATION_H

#pragma once
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <random>
#include <fstream>
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

    std::vector<Chromosome> getCurrentPopulation();

private:
    std::vector<Chromosome> chromosomes;

    void selectionEstocastic();

    std::vector<float> crossoverUniform(const std::vector<float>& parent1, const std::vector<float>& parent2, const unsigned& taxParent1, const unsigned& taxParent2);

    std::vector<float> mutationInsertion(const std::vector<float>& chromosome);

    Configuration configuration;
    void loadConfiguration();
};

#endif
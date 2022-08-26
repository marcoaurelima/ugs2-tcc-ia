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

    std::set<float> selectionEstocastic(const std::vector<float>& fitness, const unsigned& qtdNidles, const unsigned& spin);

    std::vector<float> crossoverUniform(const std::vector<float>& parent1, const std::vector<float>& parent2, const unsigned& taxParent1, const unsigned& taxParent2);

    std::vector<float> mutationInsertion(const std::vector<float>& chromosome);

};

#endif
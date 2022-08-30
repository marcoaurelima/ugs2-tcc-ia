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
    void generateNewPopulation(NewGenParams newGenParams);
    std::vector<Chromosome> getCurrentPopulation();
    void show();

private:
    std::vector<Chromosome> chromosomes;
    std::vector<unsigned> getConfig(const std::string& path);
    void selectionEstocastic();
    void crossoverUniform(); 
    void mutationInsertion(); 

};

#endif
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

    void createInitialPopulation(const unsigned populationSize, const unsigned chromossomeSize);
    void setNewGenerationParams(const NewGenParams newGenParams);
    void generateNewPopulation();
    std::vector<Chromosome> getCurrentPopulation() const;
    void show() const;

    void setChromossomeFitness(const unsigned index, const float fitness);

private:
    std::vector<Chromosome> chromosomes;
    NewGenParams newGenParams;

    std::vector<unsigned> getConfig(const std::string& path) const;
    float getRandomFloat();

    void selectionEstocastic(int qtdNidles = 0);
    void selectionRoulette();

    void crossoverUniform(); 
    void crossoverSinglePoint(int indexPointDivision = -1); 
    
    void mutationInsertion(); 
    void mutationUniform(const float MIN_VALUE = 0.0, const float MAX_VALUE = 1.0); 

};

#endif
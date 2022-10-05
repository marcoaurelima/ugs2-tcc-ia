#ifndef POPULATION_H
#define POPULATION_H

#pragma once
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>
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

    void enablePrintLogs(bool enable = true);

private:
    std::vector<Chromosome> chromosomes;
    NewGenParams newGenParams;

    std::vector<unsigned> getConfig(const std::string& path) const;
    int generateRandomInt(const int min, const int max, std::string  local);
    float generateRandomFloat(const float min, const float max);
    void  shuffleVector(std::vector<bool> & vec);

    void selectionEstocastic(int qtdNidles = 0);
    void selectionRoulette();

    void crossoverUniform(); 
    void crossoverSinglePoint(int indexPointDivision = -1); 
    
    void mutationInsertion(); 
    void mutationUniform(const float MIN_VALUE = 0.0, const float MAX_VALUE = 1.0); 

    void executeElitism();

    bool enabledLogs {false};
};

#endif
#ifndef NEUROEVOLUTIVEENGINE_H
#define NEUROEVOLUTIVEENGINE_H

#pragma once

#include <vector>
#include "GA/Population.h"
#include "NN/NeuralNetwork.h"

#include <chrono>
#include <ctime> 
#include <fstream>

class NeuroEvolutiveEngine
{
public:
    NeuroEvolutiveEngine();
    NeuroEvolutiveEngine(Population& population, NeuralNetwork& neuralNetwork);
    ~NeuroEvolutiveEngine();

    void showInternalStatus() const;
    std::vector<float> takeDecision(const std::vector<float> decision);
    void useNextTopology();
    void usePrevTopology();
    void createNewGeneration();
    void setCurrentChromossomeFitness(const float fitness);
    float getCurrentChromossomeFitness() const;

    unsigned getCurrentGenerationIndex() const;
    unsigned getCurrentGenerationSize() const;
    unsigned getCurrentChromossomeIndex() const;
    bool currentChromossomeHaveFitness() const;
    
    void saveCurrentChromossomeInFile() const;

private:
    Population population;
    NeuralNetwork neuralNetwork;

    int currentChromossomeIndex {}; // indice do cromossomo atual que preencheu a rede neural 
    int currentGenerationCount  {0}; 
    int newGenerationCount {0}; 
};

#endif
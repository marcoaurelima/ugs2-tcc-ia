#ifndef NEUROEVOLUTIVEENGINE_H
#define NEUROEVOLUTIVEENGINE_H

#pragma once

#include <vector>
#include "GA/Population.h"
#include "NN/NeuralNetwork.h"

class NeuroEvolutiveEngine
{
public:
    NeuroEvolutiveEngine(Population population, NeuralNetwork neuralNetwork);
    ~NeuroEvolutiveEngine();

    void showLogs() const;
    std::vector<float> takeDecision(const std::vector<float>& decision);
    void nextTopology();
    void prevTopology();
    void createNewGeneration();
    void setCurrentChromossomeFitness(const float fitness);
private:
    Population population;
    NeuralNetwork neuralNetwork;

    int currentChromossomeIndex {}; // indice do crmossomo atual que preencheu a rede neural 
};

#endif
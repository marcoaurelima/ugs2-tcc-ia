#ifndef NEUROEVOLUTIVEENGINE_H
#define NEUROEVOLUTIVEENGINE_H

#pragma once

#include "GA/Population.h"
#include "NN/NeuralNetwork.h"

class NeuroEvolutiveEngine
{
public:
    NeuroEvolutiveEngine(Population population, NeuralNetwork neuralNetwork);
    ~NeuroEvolutiveEngine();

    void showLogs() const;

private:
    Population population;
    NeuralNetwork neuralNetwork;
};

#endif
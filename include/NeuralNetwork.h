#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#pragma once

#include "Chromosome.h"

class NeuralNetwork
{
public:
    NeuralNetwork(unsigned inputLayerSize, unsigned hiddenLayerSize, Chromosome& chromosome );
    ~NeuralNetwork();

private:

};

#endif
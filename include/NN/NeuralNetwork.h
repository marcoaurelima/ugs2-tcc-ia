#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#pragma once

#include <vector>
#include "NN/types.h"
#include "GA/Chromosome.h"

class NeuralNetwork
{
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void setInputLayer(InputLayerInfo layer);
    void setHiddenLayer(HiddenLayerInfo layer);
    void setOutputLayer(OutputLayerInfo layer);


    std::vector<unsigned> takeDecision(std::initializer_list<unsigned> inputParams);
    
private:

};

#endif
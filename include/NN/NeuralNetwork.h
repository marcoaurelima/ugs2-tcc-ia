#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#pragma once

#include <vector>
#include "NN/types.h"

class NeuralNetwork
{
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void setInputLayer(InputLayerInfo layerInfo);
    void setHiddenLayer(HiddenLayerInfo layerInfo);
    void setOutputLayer(OutputLayerInfo layerInfo);


    std::vector<unsigned> takeDecision(std::initializer_list<float> inputParams);
    
private:
    InputLayer inputLayer;
    HiddenLayer hiddenLayer;
    OutputLayer outputLayer;
};

#endif
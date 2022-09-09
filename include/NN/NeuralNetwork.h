#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <deque>
#include "NN/types.h"

class NeuralNetwork
{
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void setInputLayer(const InputLayerInfo& layerInfo);
    void setHiddenLayer(const HiddenLayerInfo& layerInfo);
    void setOutputLayer(const OutputLayerInfo& layerInfo);

    std::vector<unsigned> takeDecision(const std::initializer_list<float> inputParams);
    
    void show() const;

    void loadDataFromFile(const std::string path);

private:
    InputLayer inputLayer;
    HiddenLayer hiddenLayer;
    OutputLayer outputLayer;

};

#endif
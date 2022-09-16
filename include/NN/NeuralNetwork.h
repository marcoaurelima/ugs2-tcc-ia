#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <deque>
#include <algorithm>
#include <cmath>
#include "NN/types.h"
#include "GA/Chromosome.h"

class NeuralNetwork
{
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void setInputLayer(const InputLayerInfo& layerInfo);
    void setHiddenLayer(const HiddenLayerInfo& layerInfo);
    void setOutputLayer(const OutputLayerInfo& layerInfo);

    std::vector<float> takeDecision(const std::vector<float>& inputParams);
    
    void show() const;

    void loadDataFromFile(const std::string path);
    void loadDataFromChromosome(const Chromosome& chromossome);
private:
    InputLayer inputLayer;
    HiddenLayer hiddenLayer;
    OutputLayer outputLayer;
    ACTFUNC activFuncHidden;
    ACTFUNC activFuncOutput;


    float normalize(float x, float xMin, float xMax, float d1, float d2) const;
};

#endif
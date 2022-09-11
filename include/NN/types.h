#ifndef NNTYPES_H
#define NNTYPES_H

#include <initializer_list>
#include "Neuron.h"

enum class ACTFUNC {
    SIGMOID,
    RELU
};

struct InputLayerInfo {
    InputLayerInfo(unsigned qtdNeurons) : qtdNeurons(qtdNeurons) {};
    unsigned qtdNeurons;
};

//using OutputLayerInfo = InputLayerInfo;

struct HiddenLayerInfo {
    HiddenLayerInfo(std::initializer_list<unsigned> sizesOfNeuronsGroups, ACTFUNC activationFunction) 
    : sizesOfNeuronsGroups(sizesOfNeuronsGroups), activationFunction(activationFunction) {};
    std::initializer_list<unsigned> sizesOfNeuronsGroups;
    ACTFUNC activationFunction;
};

struct OutputLayerInfo {
    OutputLayerInfo(unsigned qtdNeurons, ACTFUNC activationFunction) 
    : qtdNeurons(qtdNeurons), activationFunction(activationFunction) {};
    unsigned qtdNeurons;
    ACTFUNC activationFunction;
};

using InputLayer = std::vector<Neuron>;
using HiddenLayer = std::vector<std::vector<Neuron>>;
using OutputLayer = std::vector<Neuron>;


#endif
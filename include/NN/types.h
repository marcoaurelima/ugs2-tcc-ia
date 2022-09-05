#ifndef NNTYPES_H
#define NNTYPES_H

#include <initializer_list>
#include "Neuron.h"

struct InputLayerInfo {
    InputLayerInfo(unsigned qtdNeurons) : qtdNeurons(qtdNeurons) {};
    unsigned qtdNeurons;
};

using OutputLayerInfo = InputLayerInfo;

struct HiddenLayerInfo {
    HiddenLayerInfo(std::initializer_list<unsigned> sizeOfNeuronsGroups) 
    : sizeOfNeuronsGroups(sizeOfNeuronsGroups) {};
    std::initializer_list<unsigned> sizeOfNeuronsGroups;
};


using InputLayer = std::vector<Neuron>;
using HiddenLayer = std::vector<std::vector<Neuron>>;
using OutputLayer = std::vector<Neuron>;


#endif
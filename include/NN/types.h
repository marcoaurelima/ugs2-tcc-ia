#ifndef NNTYPES_H
#define NNTYPES_H

#include <initializer_list>
#include "Neuron.h"
#include "enums.h"

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


template <typename T>
void showvalues(std::string title, T container, std::string separator = "")
{
    std::cout << title << "\n------------ " << title << " ------------" << std::endl;
    for(auto i : container)
    {
        std::cout << i << separator;
    }
    std::cout << "\n-------------------------------------------\n" << std::endl;
}

#endif
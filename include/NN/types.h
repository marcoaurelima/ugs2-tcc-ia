#ifndef NNTYPES_H
#define NNTYPES_H

#include <initializer_list>

struct InputLayer {
    InputLayer(unsigned qtdNeurons) : qtdNeurons(qtdNeurons) {};
    unsigned qtdNeurons;
};

using OutputLayer = InputLayer;

struct HiddenLayer {
    HiddenLayer(std::initializer_list<unsigned> sizeOfNeuronsGroups) 
    : sizeOfNeuronsGroups(sizeOfNeuronsGroups) {};
    std::initializer_list<unsigned> sizeOfNeuronsGroups;
};

#endif
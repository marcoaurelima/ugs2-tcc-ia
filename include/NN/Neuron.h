#ifndef NEURON_H
#define NEURON_H

#pragma once

#include <vector>

using height = float;

class Neuron
{
public:
    Neuron();
    ~Neuron();

private:
    bool isActive;
    float bias;
    float value;
    std::vector<height> connections;

};

#endif
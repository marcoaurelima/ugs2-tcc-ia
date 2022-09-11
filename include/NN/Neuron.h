#ifndef NEURON_H
#define NEURON_H

#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <vector>
#include "enums.h"

using height = float;

class Neuron
{
public:
    Neuron();
    Neuron(const float bias, const float value, const std::vector<height>& connections, const bool isActive = false);
    ~Neuron();

    void setActive(const bool isActive);
    void setBias(const float bias);
    void setValue(const float value, ACTFUNC activationFunction);
    void setConnectionsHeights(const std::vector<height>& connectionsHeights);

    bool isActive() const;
    float getValue() const;
    float getBias() const;
    std::vector<height> getConnectionsHeights() const;

private:
    float bias {};
    float value {};
    std::vector<height> connectionsHeights;
    bool active {false};

    float sigmoid(float x) const;
    float reLU(float x) const;
};

#endif
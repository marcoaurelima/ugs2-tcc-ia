#ifndef NEURON_H
#define NEURON_H

#pragma once

#include <vector>

using height = float;

class Neuron
{
public:
    Neuron();
    Neuron(float bias, float value, std::vector<height> connections, bool isActive = false);
    ~Neuron();

    void setActive(bool isActive);
    void setBias(float bias);
    void setValue(float value);
    void setConnectionsHeights(std::vector<height> connectionsHeights);

    bool isActive() const;
    float getValue() const;
    float getBias() const;
    std::vector<height> getConnectionsHeights() const;

private:
    bool active {false};
    float bias {};
    float value {};
    std::vector<height> connectionsHeights;

};

#endif
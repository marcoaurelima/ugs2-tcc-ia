#include "NN/Neuron.h"

Neuron::Neuron(const float bias, const float value, const std::vector<height>& connectionsHeights, const bool active)
    : bias(bias), value(value), connectionsHeights(connectionsHeights), active(active)
    {
        //this->active = active;
    }

Neuron::Neuron() {}

Neuron::~Neuron() {}

void Neuron::setActive(bool active)
{
    this->active = active;
}

void Neuron::setBias(float bias)
{
    this->bias = bias;
}

void Neuron::setValue(float value)
{
    this->value = value;
}

void Neuron::setConnectionsHeights(const std::vector<height>& connectionsHeights)
{
    this->connectionsHeights = connectionsHeights;
}

bool Neuron::isActive() const
{
    return active;
}

float Neuron::getValue() const
{
    return value;
}

float Neuron::getBias() const
{
    return bias;
}

std::vector<height> Neuron::getConnectionsHeights() const
{
    return connectionsHeights;
}
#include "NN/Neuron.h"

Neuron::Neuron(float bias, float value, std::vector<height> connections, bool isActive)
    : bias(bias), value(value), connectionsHeights(connectionsHeights), active(active) {}

Neuron::~Neuron()
{
}

void Neuron::setActive(bool isActive)
{
}
void Neuron::setBias(float bias)
{
}
void Neuron::setValue(float value)
{
}
void setConnectionsHeights(std::vector<height> connectionsHeights)
{
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
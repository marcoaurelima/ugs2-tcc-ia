#include "NeuroEvolutiveEngine.h"

NeuroEvolutiveEngine::NeuroEvolutiveEngine(Population population, NeuralNetwork neuralNetwork)
: population(population), neuralNetwork(neuralNetwork){}


NeuroEvolutiveEngine::~NeuroEvolutiveEngine()
{

}

void NeuroEvolutiveEngine::showLogs() const
{
    population.show();
    neuralNetwork.show();
}
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

std::vector<float> NeuroEvolutiveEngine::takeDecision(const std::vector<float>& decision)
{
    return neuralNetwork.takeDecision(decision);
}

void NeuroEvolutiveEngine::createInitialTopology()
{
    int i = currentChromossomeIndex;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}
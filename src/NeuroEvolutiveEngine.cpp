#include "NeuroEvolutiveEngine.h"

NeuroEvolutiveEngine::NeuroEvolutiveEngine(Population population, NeuralNetwork neuralNetwork)
: population(population), neuralNetwork(neuralNetwork)
{
    int i = currentChromossomeIndex;
    this->neuralNetwork.loadDataFromChromosome(this->population.getCurrentPopulation()[i]);
}


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

void NeuroEvolutiveEngine::nextTopology()
{
    //int i = currentChromossomeIndex;
    //neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}
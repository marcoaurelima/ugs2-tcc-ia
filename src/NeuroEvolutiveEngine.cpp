#include "NeuroEvolutiveEngine.h"

NeuroEvolutiveEngine::NeuroEvolutiveEngine(Population population, NeuralNetwork neuralNetwork)
: population(population), neuralNetwork(neuralNetwork)
{
    int i = currentChromossomeIndex = 0;
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
    if(currentChromossomeIndex == population.getCurrentPopulation().size() - 1){ return; }

    int i = ++currentChromossomeIndex;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}

void NeuroEvolutiveEngine::prevTopology()
{
    if(currentChromossomeIndex == 0){ return; }

    int i = --currentChromossomeIndex;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}

void NeuroEvolutiveEngine::createNewGeneration()
{
    population.generateNewPopulation();
    int i = currentChromossomeIndex = 0;
    this->neuralNetwork.loadDataFromChromosome(this->population.getCurrentPopulation()[i]);
}
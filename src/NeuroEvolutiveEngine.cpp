#include "NeuroEvolutiveEngine.h"

NeuroEvolutiveEngine::NeuroEvolutiveEngine(){}

NeuroEvolutiveEngine::NeuroEvolutiveEngine(Population& population, NeuralNetwork& neuralNetwork)
    : population(population), neuralNetwork(neuralNetwork)
{
    int i = currentChromossomeIndex = 0;
    this->neuralNetwork.loadDataFromChromosome(this->population.getCurrentPopulation()[i]);
}

NeuroEvolutiveEngine::~NeuroEvolutiveEngine()
{
}

void NeuroEvolutiveEngine::showInternalStatus() const
{
    population.show();
    neuralNetwork.show();
}

std::vector<float> NeuroEvolutiveEngine::takeDecision(const std::vector<float> inputParams)
{
    return neuralNetwork.takeDecision(inputParams);

}

// Preenche a rede com a proxima topologia presente no cromossomo
// quando não chegar no ultimo cromossomo e esta função for chamada
// significa que todas as topologias foram testadas, mas não obtiveram
// uma performance aceitável. Por isso, será criado uma nova população
// de cromossomos baseadas em elitismo.
void NeuroEvolutiveEngine::useNextTopology()
{
    if (currentChromossomeIndex == (int)population.getCurrentPopulation().size() - 1)
    {
        puts("[+] Nova Populacao ---\n");

        population.generateNewPopulation();

        int i = currentChromossomeIndex = 0;
        neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);

        currentGenerationCount = 1;
        newGenerationCount++;
        return;
    }

    int j = ++currentChromossomeIndex;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[j]);
    currentGenerationCount++;
}

void NeuroEvolutiveEngine::usePrevTopology()
{
    if (currentChromossomeIndex == 0)
    {
        return;
    }

    int i = --currentChromossomeIndex;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}

void NeuroEvolutiveEngine::createNewGeneration()
{
    population.generateNewPopulation();
    int i = currentChromossomeIndex = 0;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}

void NeuroEvolutiveEngine::setCurrentChromossomeFitness(const float fitness)
{
    int i = currentChromossomeIndex;
    population.setChromossomeFitness(i, fitness);
}


unsigned NeuroEvolutiveEngine::getCurrentGenerationIndex() const
{
    return currentGenerationCount;
}

unsigned NeuroEvolutiveEngine::getCurrentChromossomeIndex() const
{
    return newGenerationCount;
}

unsigned NeuroEvolutiveEngine::getCurrentGenerationSize() const
{
    return population.getCurrentPopulation().size();
}

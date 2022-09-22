#include "NeuroEvolutiveEngine.h"

NeuroEvolutiveEngine::NeuroEvolutiveEngine(){}

NeuroEvolutiveEngine::NeuroEvolutiveEngine(Population population, NeuralNetwork neuralNetwork)
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

std::vector<float> NeuroEvolutiveEngine::takeDecision(const std::vector<float> &decision)
{
    return neuralNetwork.takeDecision(decision);
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
        std::cout << "======== CRIANDO NOVA POPULAÇÃO ========\n\n\n\n";
        population.generateNewPopulation();

        int i = currentChromossomeIndex = 0;
        neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
        return;
    }

    int j = ++currentChromossomeIndex;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[j]);
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
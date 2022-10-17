#include "NeuroEvolutiveEngine.h"

NeuroEvolutiveEngine::NeuroEvolutiveEngine() {}

NeuroEvolutiveEngine::NeuroEvolutiveEngine(Population &population, NeuralNetwork &neuralNetwork)
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
    //std::cout << "NeuroEvolutiveEngine::takeDecision" << std::endl;

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
        puts("\n[+] Nova Populacao ---\n");

        population.executeElitism(100);
        population.generateNewPopulation();
        int i = currentChromossomeIndex = 0;
        neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
        // currentGenerationCount = 0;
        newGenerationCount++;
        return;
    }

    // todos os cromossomos começam com valor 0 no fitness
    // isto significa que se há um lvalor de fitness em um cromossomo diferente
    // de 0, ele já foi testado e tem un fitness válido e não precisará de treinamento.

    // pular cromossomos já treinados.
    // int i = currentGenerationCount++;
    int j = currentChromossomeIndex++;

    //std::cout << "   j: " << j << std::endl;

    /*
    if (population.getCurrentPopulation()[j].haveFitness())
    {
        //++currentChromossomeIndex;
        currentGenerationCount++;

        std::cout << "Cromossomo [" << i << "] Fitness: " << population.getCurrentPopulation()[j].getFitness() << std::endl;
        neuralNetwork.show();
        return;
    }
    */

    ///neuralNetwork.show();

    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[j]);
    // currentGenerationCount++;
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
    population.executeElitism(100);
    population.generateNewPopulation();
    int i = currentChromossomeIndex = 0;
    neuralNetwork.loadDataFromChromosome(population.getCurrentPopulation()[i]);
}

void NeuroEvolutiveEngine::setCurrentChromossomeFitness(const float fitness)
{
    int i = currentChromossomeIndex;
    population.setChromossomeFitness(i, fitness);
}

float NeuroEvolutiveEngine::getCurrentChromossomeFitness() const
{
    unsigned i = currentChromossomeIndex;
    return population.getCurrentPopulation()[i].getFitness();
}

unsigned NeuroEvolutiveEngine::getCurrentGenerationIndex() const
{
    return currentChromossomeIndex;
}

unsigned NeuroEvolutiveEngine::getCurrentChromossomeIndex() const
{
    return newGenerationCount;
}

unsigned NeuroEvolutiveEngine::getCurrentGenerationSize() const
{
    return population.getCurrentPopulation().size();
}

bool NeuroEvolutiveEngine::currentChromossomeHaveFitness() const
{
    unsigned i = currentChromossomeIndex;
    return population.getCurrentPopulation()[i].haveFitness();
}

void NeuroEvolutiveEngine::saveCurrentChromossomeInFile() const
{
    unsigned relevantFitnessValue = 100;
    if(getCurrentChromossomeFitness() < relevantFitnessValue){ return; }

    std::time_t result = std::time(nullptr);
    std::string now(std::ctime(&result));

    std::stringstream filename;
    filename << "logs/G-"
             << getCurrentChromossomeIndex() << " C-"
             << getCurrentGenerationIndex() << "-"
             << now.substr(0, now.size() - 1)
             << getCurrentGenerationSize() << " F-"
             << getCurrentChromossomeFitness() << " "
             << ".log";

    std::stringstream fileContents;

    unsigned index = currentChromossomeIndex;
    for (unsigned i = 0; i < population.getCurrentPopulation()[index].getAllGenes().size(); i++)
    {
        fileContents << population.getCurrentPopulation()[index].getAllGenes()[i] << " ";
    }

    std::string filenameCorr;
    for (unsigned i = 0; i < filename.str().size(); i++)
    {
        if (filename.str()[i] == ' ')
        {
            filenameCorr += R"(   )";
            continue;
        }
        else if (filename.str()[i] == ':')
        {
            filenameCorr += '-';
            continue;
        }

        filenameCorr += filename.str()[i];
    }

    std::ofstream file;
    file.open(filenameCorr, std::ofstream::out);
    if (!file.is_open())
    {
        std::cerr << "Error: " << filenameCorr << std::endl;
    }

    file << fileContents.str();
    file.close();
}

unsigned NeuroEvolutiveEngine::getRecordFitness() const
{
    return population.getRecordFitness();
}
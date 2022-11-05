#include <iostream>
#include <fstream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "GA/Population.h"
#include "GA/types.h"

#include "NN/types.h"
#include "NN/NeuralNetwork.h"

#include "NeuroEvolutiveEngine.h"

#include "GeneticServer.h"

using std::cout;
int main()
{
    GeneticServer server;
    
    // população inicial
    Population population;
    population.enablePrintLogs();
    population.createInitialPopulation(100, 44);
    population.show();
    population.setNewGenerationParams(NewGenParams{
        SELECTION_TYPE::ROULLETE,
        CROSSOVER_TYPE::UNIFORM,
        MUTATION_TYPE::UNIFORM});

    population.show();

    // definição da topologia da rede neural
    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(3));
    network.setHiddenLayer(HiddenLayerInfo({4, 4}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));
   
    // Dados do jogo em tempo real
    float pontuation = 0.5, distance = 0.1; int value = 0.1;

    NeuroEvolutiveEngine engine(population, network);
    engine.showInternalStatus();

    srand(time(NULL));

    exit(0);
    
    for(;;)
    {
        auto d = engine.takeDecision({10, 20});

        std::cout << "decision: " << d[0] << std::endl;
        
        engine.setCurrentChromossomeFitness(rand()%100);

        engine.useNextTopology();
    }

/*
    for (unsigned i = 0; i < population.getCurrentPopulation().size()+2; i++)
    {
        network.loadDataFromChromosome(population.getCurrentPopulation()[i]);
        //network.show();
        auto d = network.takeDecision({10, 20});

        std::cout << "decision: " << d[0] << std::endl;
    }*/

    return 0;
}
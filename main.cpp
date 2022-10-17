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

using std::cout;
int main()
{

    // população inicial
    Population population;
    population.enablePrintLogs();
    population.createInitialPopulation(10, 27);
    population.show();
    population.setNewGenerationParams(NewGenParams{
        SELECTION_TYPE::ROULLETE,
        CROSSOVER_TYPE::UNIFORM,
        MUTATION_TYPE::UNIFORM});
/*
    population.setChromossomeFitness(0, 500);
    population.setChromossomeFitness(1, 70);
    population.setChromossomeFitness(2, 853);
    population.setChromossomeFitness(3, 1230);
    population.setChromossomeFitness(4, 35553);
    population.setChromossomeFitness(5, 45454);
    population.setChromossomeFitness(6, 345);
    population.setChromossomeFitness(7, 56);
    population.setChromossomeFitness(8, 2345);
    population.setChromossomeFitness(9, 7063);
*/
    //population.generateNewPopulation();
    population.show();

    // definição da topologia da rede neural
    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));
   
    // Dados do jogo em tempo real
    float pontuation = 0.5, distance = 0.1; int value = 0.1;

    NeuroEvolutiveEngine engine(population, network);
    engine.showInternalStatus();

    srand(time(NULL));

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
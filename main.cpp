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
    population.createInitialPopulation(4, 27);
    population.show();
    population.setNewGenerationParams(NewGenParams{
        SELECTION_TYPE::ROULLETE,
        CROSSOVER_TYPE::UNIFORM,
        MUTATION_TYPE::UNIFORM});

    population.setChromossomeFitness(0, 500);
    population.setChromossomeFitness(1, 70);
    population.setChromossomeFitness(2, 853);
    population.setChromossomeFitness(3, 1230);

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
    //engine.showInternalStatus();

    for (int i = 0; i < 104; i++)
    {
        std::cout << "--------------------------------\n";
        value += 0.1;
        pontuation += value;
        distance += value;
        //engine.showInternalStatus();
        auto r = engine.takeDecision({pontuation, distance});
        cout << "Decision1: " << r[0] << endl;
        engine.setCurrentChromossomeFitness(value);
        //engine.showInternalStatus();

        //engine.useNextTopology();
        std::cout << "--------------------------------\n";
    }

    /*
    */
/*
    for (unsigned i = 0; i < population.getCurrentPopulation().size(); i++)
    {
        network.loadDataFromChromosome(population.getCurrentPopulation()[i]);
        //network.show();
        auto d = network.takeDecision({10, 20});

        std::cout << "decision: " << d[0] << std::endl;
    }
*/
    // network.loadDataFromChromosome({0,1,2,3, 0,4,5,6,   0,1,2,3, 0,4,5,6, 0,1,2,3, 0,1, 0,2, 0,3, 0});
    // network.loadDataFromChromosome({1,2,3,4, 5,6,7,8, 9,0,1,2, 3,4,5,6, 7,8,9,0, 1,2, 3,4, 5,6, 7});
    // network.show();

    return 0;
}
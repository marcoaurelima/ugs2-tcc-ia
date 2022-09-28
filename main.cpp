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
    population.setNewGenerationParams(NewGenParams{
        SELECTION_TYPE::ROULLETE,
        CROSSOVER_TYPE::UNIFORM,
        MUTATION_TYPE::UNIFORM});
    population.show();
    population.generateNewPopulation();

    // definição da topologia da rede neural
    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));


    /*
    // Dados do jogo em tempo real
    float pontuation = 20.0, distance = 5.0, value = 0.0;

    NeuroEvolutiveEngine engine(population, network);
    engine.showInternalStatus();


    auto r = engine.takeDecision({pontuation, distance});


    for (int i = 0; i < 15; i++)
    {
        value += 0.01;
        auto r = engine.takeDecision({pontuation, distance});
        cout << "Decision1: " << r[0] << endl;
        engine.setCurrentChromossomeFitness(value);
        //engine.showInternalStatus();

        engine.useNextTopology();
    }
    */
    return 0;
}
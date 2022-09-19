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
    population.createInitialPopulation(5, 27);
    population.setNewGenerationParams(NewGenParams{
        SELECTION_TYPE::ROULLETE,
        CROSSOVER_TYPE::SINGLE_POINT,
        MUTATION_TYPE::INSERTION});

    // definição da topologia da rede neural
    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));

    // Dados do jogo em tempo real
    float pontuation = 20.0, distance = 5.0;

    NeuroEvolutiveEngine engine(population, network);

    //engine.setCurrentChromossomeFitness(5.55);

    engine.showLogs();
    float r = engine.takeDecision(std::vector<float>{pontuation, distance})[0];
    cout << "Decision1: " << r << endl;
    engine.setCurrentChromossomeFitness(6.66);

    engine.nextTopology();
    engine.showLogs();
    r = engine.takeDecision(std::vector<float>{pontuation, distance})[0];
    engine.setCurrentChromossomeFitness(7.77);
    cout << "Decision2: " << r << endl;

    engine.showLogs();

    return 0;
}
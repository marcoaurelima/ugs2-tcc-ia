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

// testando commit

int main()
{

    NeuralNetwork network;

    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}));
    network.setOutputLayer(OutputLayerInfo(1));
    network.loadDataFromFile("configurations/NN/network-data.ini");

    float pontuation = 0, distance = 0;
    network.takeDecision({pontuation, distance});

    network.show();

    /*

    Population population;
    population.createInitialPopulation(8,10);
    population.show();

    NewGenParams newGenParams;
    newGenParams.selectionType = SELECTION_TYPE::ROULLETE;
    newGenParams.crossoverType = CROSSOVER_TYPE::SINGLE_POINT;
    newGenParams.mutationType  = MUTATION_TYPE::INSERTION;

    population.generateNewPopulation(newGenParams);
    */

    return 0;
}
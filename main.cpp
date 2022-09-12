#include <iostream>
#include <fstream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include "GA/Population.h"
#include "GA/types.h"

#include "NN/types.h"
#include "NN/NeuralNetwork.h"


float sigmoid(float x)
{
    return 1 / (1 + std::pow(std::exp(1), -x));
}

float reLU(float x)
{
    return (x > 0) ? x : 0;
}

int main()
{

    std::cout << "sigmoid: " << sigmoid(5) << std::endl; 
    std::cout << "reLU: " << reLU(1) << std::endl; return 0;


    NeuralNetwork network;

    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({4, 3}, ACTFUNC::RELU));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));
    network.loadDataFromFile("configurations/NN/network-data.ini");
    
    network.show();

    float pontuation = 20, distance = 5;
    network.takeDecision(std::vector<float>{pontuation, distance});

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
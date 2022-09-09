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


float sigmoid(float x)
{
    return 1 / (1 + std::pow(std::exp(1), -x));
}

float reLU(float x)
{
    return (x > 0) ? x : 0;
}


// [x]         valor a ser normalizado
// [xMin xMax] variação do valor de x
// [d1 d2]     Limite ao qual o valor de x será reduzido
float normalize(float x, float xMin, float xMax, float d1, float d2)
{
    return (((x - xMin) * (d2 - d1)) / (xMax - xMin)) + d1;
}

int main()
{

    std::cout << "sigmoid: " << sigmoid(5) << std::endl; 
    std::cout << "reLU: " << reLU(1) << std::endl; 
    std::cout << "normalize: " << normalize(25, 0, 1234, 0, 1) << std::endl; return 0;



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
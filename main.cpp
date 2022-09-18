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


int main()
{    

    Population population;
    population.createInitialPopulation(5,27);
    population.setFitness(0, 11);
    population.setFitness(1, 123);
    population.show(); 

    


    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));

    network.loadDataFromChromosome(population.getCurrentPopulation()[0]);

    network.show();

    float pontuation = 20, distance = 5;
    float decision = network.takeDecision(std::vector<float>{pontuation, distance})[0];

    network.show();

    std::cout << "Decision: " << decision << std::endl;
    exit(0);


    NewGenParams newGenParams;
    newGenParams.selectionType = SELECTION_TYPE::ROULLETE;
    newGenParams.crossoverType = CROSSOVER_TYPE::SINGLE_POINT;
    newGenParams.mutationType  = MUTATION_TYPE::INSERTION;

    population.generateNewPopulation(newGenParams);
    

    
    

    return 0;
}
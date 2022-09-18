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
    // Dados do jogo em tempo real
    float pontuation = 20, distance = 5;
    unsigned errors = 0;
    bool isPressed = false;

    // população inicial
    Population population;
    population.createInitialPopulation(5,27);
    population.setNewGenerationParams(
        NewGenParams {
            SELECTION_TYPE::ROULLETE,
            CROSSOVER_TYPE::SINGLE_POINT,
            MUTATION_TYPE::INSERTION
        }
    );

    population.show(); 

    exit(0);    
    // definição da topologia da rede neural
    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));
    network.show();

    // contador de cromossomos
    unsigned count = 0;


    network.loadDataFromChromosome(population.getCurrentPopulation()[count]);

    float decision = network.takeDecision(std::vector<float>{pontuation, distance})[0];

    network.show();

    std::cout << "Decision: " << decision << std::endl;
    //exit(0);

    std::cout << "================================================\n\n";

    
    population.generateNewPopulation();
    
    population.show();

    
    

    return 0;
}
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
    // população inicial
    Population population;
    population.enablePrintLogs();
    population.createInitialPopulation(100, 44);
    population.show();
    population.setNewGenerationParams(
        NewGenParams{
            SELECTION_TYPE::ROULLETE,
            CROSSOVER_TYPE::UNIFORM,
            MUTATION_TYPE::UNIFORM});

    GeneticServer server(&population);
    server.setPort(45001);
    server.start();

    return 0;
}
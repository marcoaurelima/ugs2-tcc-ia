#include <iostream>
#include <fstream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "Population.h"
#include "types.h"


struct Configuration
{
    struct Selection{
        std::pair<std::string, std::string> fitness;
        std::pair<std::string, std::string> tournament;
        std::pair<std::string, unsigned> roullete;
        std::pair<std::string, unsigned> estocastic;
    } selection;

    struct Crossover{
        std::pair<std::string, unsigned> singlepoint;
        std::pair<std::string, std::vector<unsigned>> multipoint;
        std::pair<std::string, std::string> uniform;
    } crossover;

    struct Mutation{
        std::pair<std::string, std::string> insertion;
        std::pair<std::string, std::string> inversion;
        std::pair<std::string, std::string> uniform;
    } mutation;
};


void getconfiguration()
{
    Configuration configuration;

    std::ifstream file("GAConfiguration.ini");


    std::string key, value;

    // selection/fitness
    file >> key; file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    configuration.selection.fitness = std::make_pair(key, value);

    // selection/tournament
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    // selection/roullete
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    // selection/estocastic
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    std::cout << "--------------------------------\n";

    // crossover/singlepoint
    file >> key; file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    configuration.selection.fitness = std::make_pair(key, value);

    // crossover/multipoint
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    // crossover/uniform
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    std::cout << "--------------------------------\n";

    // mutation/insertion
    file >> key; file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    configuration.selection.fitness = std::make_pair(key, value);

    // mutation/inversion
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    // mutation/uniform
    file >> key; 
    file >> key >> value;
    std::cout << key << " " << value << std::endl;
    
    std::cout << "--------------------------------\n";




}

int main(int argc, char **argv) 
{

    getconfiguration();
    return 0;

    Population population;
    population.createInitialPopulation(3,20);
    population.show();

    NewGenParams newGenParams;
    newGenParams.selectionType = SELECTION_TYPE::FITNESS;
    newGenParams.crossoverType = CROSSOVER_TYPE::MULTI_POINT;
    newGenParams.mutationType  = MUTATION_TYPE::INSERTION;

    population.generateNewPopulation(newGenParams);

    return 0;
}
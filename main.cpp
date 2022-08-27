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


Configuration getconfiguration()
{
    std::ifstream file("GAConfiguration.ini");
    Configuration configuration;
    std::string key, value;

    // selection/fitness
    file >> key; file >> key; 
    file >> key >> value;
    configuration.selection.fitness = std::make_pair(key, value);

    // selection/tournament
    file >> key; 
    file >> key >> value;
    configuration.selection.tournament = std::make_pair(key, value);
    
    // selection/roullete
    file >> key; 
    file >> key >> value;
    configuration.selection.roullete = std::make_pair(key, (unsigned)std::stoi(value));

    // selection/estocastic
    file >> key; 
    file >> key >> value;
    configuration.selection.estocastic = std::make_pair(key, (unsigned)std::stoi(value));
    
    // crossover/singlepoint
    file >> key; file >> key; 
    file >> key >> value;
    configuration.crossover.singlepoint = std::make_pair(key, (unsigned)std::stoi(value));

    // crossover/multipoint
    file >> key; 
    file >> key >> value;
    std::vector<unsigned> value_vector;
    for(auto& i : value)
    {
        if(i != '-') { value_vector.push_back(atoi(&i)); }
    }
    configuration.crossover.multipoint = std::make_pair(key, value_vector);
    
    // crossover/uniform
    file >> key; 
    file >> key >> value;
    configuration.crossover.uniform = std::make_pair(key, value);

    // mutation/insertion
    file >> key; file >> key; 
    file >> key >> value;
    configuration.mutation.insertion = std::make_pair(key, value);

    // mutation/inversion
    file >> key; 
    file >> key >> value;
    configuration.mutation.inversion = std::make_pair(key, value);
    
    // mutation/uniform
    file >> key; 
    file >> key >> value;
    configuration.mutation.uniform = std::make_pair(key, value);
    
    return configuration;

}

int main(int argc, char **argv) 
{

    Configuration c = getconfiguration();

    std::cout << c.crossover.multipoint.second[1] << std::endl;


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
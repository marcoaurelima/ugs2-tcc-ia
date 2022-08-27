#include <iostream>
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
        std::pair<std::string, std::vector<bool>> uniform;
    } crossover;

    struct Mutation{
        std::pair<std::string, std::string> insertion;
        std::pair<std::string, std::string> inversion;
        std::pair<std::string, std::string> uniform;
    } mutation;
};


void getconfiguration()
{
    std::cout << "Configuration: " << std::endl;

    FILE *file = fopen("GAConfiguration.ini", "r");

    fseek(file, 7, SEEK_SET);

    char* content = NULL;

    fscanf(file, "%s", content);

    std::cout << content << std::endl;

    Configuration configuration;

    configuration.selection.estocastic = std::make_pair("asd", "dnhj");


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
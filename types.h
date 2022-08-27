#ifndef TYPES_H
#define TYPES_H

enum class SELECTION_TYPE 
{
    FITNESS,
    TOURNAMENT,
    ROULLETE,
    ESTOCASTIC
};

enum class CROSSOVER_TYPE 
{
    SINGLE_POINT,
    MULTI_POINT,
    UNIFORM
};

enum class MUTATION_TYPE 
{
    INSERTION,
    INVERSION,
    UNIFORM
};

struct NewGenParams
{
    SELECTION_TYPE selectionType;
    CROSSOVER_TYPE crossoverType;
    MUTATION_TYPE  mutationType;
};

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

#endif

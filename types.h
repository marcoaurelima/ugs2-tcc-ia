#ifndef TYPES_H
#define TYPES_H

enum class SELECTION_TYPE 
{
    FITNESS,
    TOURNAMENT,
    ROULLETE,
    AUESTOCASTIC
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

#endif

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#pragma once

#include <iostream>
#include <vector>

class Chromosome
{
public:
    Chromosome();
    Chromosome(const std::initializer_list<float> valuesList);
    Chromosome(const std::vector<float> valuesList);
    void setFitness(float fitness);
    float getFitness();
    void show();

    void setGene(float value);
    float getGene(const unsigned index);
    std::vector<float> getAllGenes();
    void setAllGenes(std::vector<float> genes);

    void setRandomFitness();

private:
    float fitness {}; 
    std::vector<float> genes;
};

#endif
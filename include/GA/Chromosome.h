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
    void setRandomFitness();
    void setGene(float value);
    void setAllGenes(std::vector<float> genes);

    float getFitness();
    float getGene(const unsigned index);
    std::vector<float> getAllGenes();
    size_t getSize();
    void show();

private:
    float fitness {}; 
    std::vector<float> genes;
};

#endif
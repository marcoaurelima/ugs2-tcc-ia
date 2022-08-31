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

    float getFitness() const;
    float getGene(const unsigned index) const;
    std::vector<float> getAllGenes() const;
    size_t getSize() const;
    void show() const;

private:
    float fitness {}; 
    std::vector<float> genes;
};

#endif
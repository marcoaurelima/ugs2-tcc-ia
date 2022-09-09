#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

class Chromosome
{
public:
    Chromosome();
    Chromosome(const std::initializer_list<float> valuesList);
    Chromosome(const std::vector<float>& valuesList);
    
    void setFitness(const float fitness);
    void setRandomFitness();
    void setGene(const float value);
    void changeGene(const unsigned index, const float value);
    void setAllGenes(const std::vector<float>& genes);


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
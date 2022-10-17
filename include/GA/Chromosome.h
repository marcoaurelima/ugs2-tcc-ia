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
    
    void setFitness(const unsigned fitness);
    void setRandomFitness();
    void setGene(const float value);
    void changeGene(const unsigned index, const float value);
    void setAllGenes(const std::vector<float>& genes);


    unsigned getFitness() const;
    float getGene(const unsigned index) const;
    std::vector<float> getAllGenes() const;
    size_t getSize() const;
    void show() const;

    bool haveFitness() const;
    void resetFitness();
private:
    bool fitnessWasDefined {false};
    unsigned fitness {}; // O fitness varia de 0 a 10000
    std::vector<float> genes;
};

#endif
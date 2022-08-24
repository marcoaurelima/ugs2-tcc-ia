#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#pragma once

#include <iostream>
#include <vector>

class Chromosome
{
public:
    Chromosome(const unsigned SIZE);
    void setFitness(float fitness);
    float getFitness();
    void show();

private:
    float fitness {}; 
    std::vector<float> values;
};

#endif
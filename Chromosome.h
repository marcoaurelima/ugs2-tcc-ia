#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#pragma once

#include <iostream>
#include <vector>

class Chromosome
{
public:
    Chromosome(const unsigned SIZE);
    ~Chromosome();

    void show();

private:
    std::vector<float> values;
};

#endif
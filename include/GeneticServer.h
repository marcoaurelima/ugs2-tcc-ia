#ifndef GENETICSERVER_H
#define GENETICSERVER_H

#pragma once

#include "GA/Population.h"
#include <SFML/Network.hpp>

class GeneticServer
{
public:
    GeneticServer();
    GeneticServer(Population* population);
    ~GeneticServer();

    void setPort(unsigned port);
    void start();

    void test();

private:
    Population* population;
    unsigned port;
    Chromosome currentChromossome;
    unsigned generationCount {};
    unsigned chromosomeCount {};

    void next();
};

#endif
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

private:
    Population* population;
    unsigned port;
    Chromosome currentChromossome;
    
    sf::Int32 generationCount {};
    sf::Int32 generationSize {};
    sf::Int32 chromosomeCount {};

    void next();
};

#endif
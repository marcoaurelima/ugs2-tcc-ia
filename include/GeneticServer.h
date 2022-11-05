#ifndef GENETICSERVER_H
#define GENETICSERVER_H

#pragma once

#include "GA/Population.h"
#include <SFML/Network.hpp>

class GeneticServer
{
public:
    GeneticServer();
    GeneticServer(Population& population);
    ~GeneticServer();

    void setAddress(std::string address, unsigned port);
    void start();

    void test();

private:
    std::string address;
    unsigned port;
};

#endif
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <deque>
#include <algorithm>
#include <cmath>
#include "NN/types.h"
#include "GA/Chromosome.h"
#include "../utils.h"

#include <SFML/Network.hpp>

using std::cout;
using std::endl;

struct ServerRequest
{
    sf::Int32 generationID {-1};
    sf::Int32 chromossomeID {-1};
    sf::Int32 fitnessValue {-1};
};

class NeuralNetwork
{
public:
    NeuralNetwork();
    ~NeuralNetwork();

    void setInputLayer(const InputLayerInfo& layerInfo);
    void setHiddenLayer(const HiddenLayerInfo& layerInfo);
    void setOutputLayer(const OutputLayerInfo& layerInfo);

    std::vector<float> takeDecision(const std::vector<float>& inputParams);
    
    void show() const;

    void loadDataFromFile(const std::string path);
    void loadDataFromChromosome(const Chromosome& chromossome);
    void getNewChromossomeFromServer(ServerRequest request);
    void setServerAddress(std::string ip, unsigned short port);
    void connectToServer();

    static float normalize(float x, float xMin, float xMax, float d1, float d2);

    int getCurrentGenerationID() const;
    int getCurrentGenerationSIZE() const;
    int getCurrentChromossomeID() const;

private:
    InputLayer inputLayer;
    HiddenLayer hiddenLayer;
    OutputLayer outputLayer;
    ACTFUNC ACTIVFUNC_HIDDEN;
    ACTFUNC ACTIVFUNC_OUTPUT;

    std::string serverIP;
    unsigned short serverPORT;

    sf::TcpSocket* socket;
    bool isConnected {};

    sf::Int32 currentGenerationID {};
    sf::Int32 currentGenerationSIZE {};
    sf::Int32 currentChromossomeID {};
};

#endif
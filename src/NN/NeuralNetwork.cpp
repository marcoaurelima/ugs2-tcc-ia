#include "NN/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::show() const 
{
    std::cout << std::endl;
    std::cout << "------ INPUT LAYER ------" << std::endl;
    std::cout << "- size: " <<  inputLayer.size() << std::endl << std::endl;

    std::cout << "------ HIDDEN LAYER ------" << std::endl;
    std::cout << "- size: " <<  hiddenLayer.size() << "   ";
    for(size_t i=0;i<hiddenLayer.size();i++)
    {
        std::cout << "Group[" << i << "]: " << hiddenLayer[i].size() << "    ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "------ OUTPUT LAYER ------" << std::endl;
    std::cout << "- size: " <<  outputLayer.size() << std::endl << std::endl;
}

void NeuralNetwork::setInputLayer(InputLayerInfo layerInfo)
{
    inputLayer = std::vector<Neuron>(layerInfo.qtdNeurons);
}


void NeuralNetwork::setHiddenLayer(HiddenLayerInfo layerInfo)
{
    for(auto groupSize : layerInfo.sizesOfNeuronsGroups)
    {
        hiddenLayer.push_back(std::vector<Neuron>(groupSize));
    }
}


void NeuralNetwork::setOutputLayer(OutputLayerInfo layerInfo)
{
    outputLayer = std::vector<Neuron>(layerInfo.qtdNeurons);
}


std::vector<unsigned> NeuralNetwork::takeDecision(std::initializer_list<float> inputParams)
{
    for(auto i : inputParams)
    return std::vector<unsigned>((unsigned)i);

    return std::vector<unsigned>(0);
}

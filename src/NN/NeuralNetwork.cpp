#include "NN/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::~NeuralNetwork() {}

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

}

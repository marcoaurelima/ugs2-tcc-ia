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

void NeuralNetwork::loadDataFromFile(const std::string path)
{
    // Preencher os valores dos neuronios da camada de entrada 

    std::ifstream file(path);
    if(!file.is_open()) { std::cerr << "[Error] File '" << path << "' not found!"<< std::endl; return; }


    std::string v;
    file >> v;

    
    std::vector<std::vector<float>> values;
    std::vector<float> value;
    while(file >> v)
    { 
        if(v == "\\")
        {
            values.push_back(value);
            value.clear();
        } else
        {
            value.push_back(std::stof(v));
        }
        //std::cout << "#: " << v << std::endl;
    }
//exit(0);
    for(auto& value : values)
    {
        for(auto& v : value)
        {
            std::cout << v;
        }
            std::cout << std::endl;
    }








}
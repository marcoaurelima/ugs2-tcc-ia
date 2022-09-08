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

void NeuralNetwork::loadDataFromFile(const std::string& path)
{
    // Preencher os valores dos neuronios da camada de entrada 

    std::ifstream file(path);
    if(!file.is_open()) { std::cerr << "[Error] File '" << path << "' not found!"<< std::endl; return; }

    // [0]: Camada de entrada   [1]: Camada oculta   [2]: Camada de Saída
    unsigned layerCount = 0;
    enum layerType 
    {
        INPUT,
        HIDDEN,
        OUTPUT
    };

    std::string value;
    file >> value;

    //unsigned count = 0;
    
    std::vector<float> values;
    while(file >> value)
    { 
        if(value == "\\")
        {
            values.clear();
            if(layerCount == layerType::INPUT)
            {
                inputLayer[0].setValue(values[0]); 
                inputLayer[0].setBias(values[1]); 
                
                std::vector<float> heights;
                for(size_t i = 2; i < values.size(); i++)
                {
                    heights.push_back(values[i]);
                }
                inputLayer[0].setConnections(heights);
            }


            layerCount++;
        }
        values.push_back(std::stof(value));

        std::cout << "#: " << value << std::endl;
    }









}
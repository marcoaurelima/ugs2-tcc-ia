#include "NN/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::show() const
{
    std::cout << std::endl;
    std::cout << "\n------ INPUT LAYER ------" << std::endl;
    std::cout << "- size: " << inputLayer.size() << std::endl;
    for (size_t i = 0; i < inputLayer.size(); i++)
    {
        std::cout << "neuron[" << i << "]:"
                  << " Value: (" << inputLayer[i].getValue()
                  << ")  Bias: (" << inputLayer[i].getBias()
                  << ")  Connections: ";

        for (auto h : inputLayer[i].getConnectionsHeights())
        {
            std::cout << "(" << h << ") ";
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n------ HIDDEN LAYER ------" << std::endl;
    unsigned hiddenLayerSize = 0;
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        hiddenLayerSize += hiddenLayer[i].size();
    }
    std::cout << "- size: " << hiddenLayerSize << "   ";
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        std::cout << "Group Size[" << i << "]: " << hiddenLayer[i].size() << "    ";
    }

    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        std::cout << "\nGroup[" << i << "]: \n";
        for (size_t j = 0; j < hiddenLayer[i].size(); j++)
        {
            std::cout << "   neuron[" << i << "]"
                      << "[" << j << "] "
                      << " Value: (" << hiddenLayer[i][j].getValue()
                      << ")  Bias: (" << hiddenLayer[i][j].getBias()
                      << ")  Connections: ";

            for (auto h : hiddenLayer[i][j].getConnectionsHeights())
            {
                std::cout << "(" << h << ") ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\n\n------ OUTPUT LAYER ------" << std::endl;
    std::cout << "- size: " << outputLayer.size() << std::endl;
    for (size_t i = 0; i < outputLayer.size(); i++)
    {
        std::cout << "neuron[" << i << "]:"
                  << " Value: (" << outputLayer[i].getValue()
                  << ")  Bias: (" << outputLayer[i].getBias()
                  << ")  Connections: ";

        for (auto h : outputLayer[i].getConnectionsHeights())
        {
            std::cout << "(" << h << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void NeuralNetwork::setInputLayer(InputLayerInfo layerInfo)
{
    inputLayer = std::vector<Neuron>(layerInfo.qtdNeurons);
}

void NeuralNetwork::setHiddenLayer(HiddenLayerInfo layerInfo)
{
    for (auto groupSize : layerInfo.sizesOfNeuronsGroups)
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
    for (auto i : inputParams)
        return std::vector<unsigned>((unsigned)i);

    return std::vector<unsigned>(0);
}

void NeuralNetwork::loadDataFromFile(const std::string path)
{
    // Preencher os valores dos neuronios da camada de entrada

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "[Error] File '" << path << "' not found!" << std::endl;
        return;
    }

    std::string v;
    file >> v;

    std::deque<std::vector<float>> values;
    std::vector<float> value;
    while (file >> v)
    {
        if (v == "\\")
        {
            values.push_back(value);
            value.clear();
            continue;
        }

        value.push_back(std::stof(v));
    }

    // Inserir dados coletados nos neuronios decada camada

    // Camada de entrada
    for (size_t i = 0; i < inputLayer.size(); i++)
    {
        inputLayer[i].setValue(values[i][0]);
        inputLayer[i].setBias(values[i][1]);

        std::vector<float> weights;
        for (size_t j = 2; j < values[i].size(); j++)
        {
            weights.push_back(values[i][j]);
        }
        inputLayer[i].setConnectionsHeights(weights);
    }
    for (size_t i = 0; i < inputLayer.size(); i++)
    {
        values.pop_front();
    }

    // Camada oculta
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        for (size_t j = 0; j < hiddenLayer[i].size(); j++)
        {
            hiddenLayer[i][j].setValue(values[j][0]);
            hiddenLayer[i][j].setBias(values[j][1]);

            std::vector<float> weights;
            for (size_t k = 2; k < values[i].size(); k++)
            {
                weights.push_back(values[j][k]);
            }
            hiddenLayer[i][j].setConnectionsHeights(weights);
        }
        for (size_t k = 0; k < hiddenLayer[i].size(); k++)
        {
            values.pop_front();
        }
    }

    // Camada de saida
    for (size_t i = 0; i < outputLayer.size(); i++)
    {
        outputLayer[i].setValue(values[i][0]);
        outputLayer[i].setBias(values[i][1]);

        std::vector<float> weights;
        for (size_t j = 2; j < values[i].size(); j++)
        {
            weights.push_back(values[i][j]);
        }
        outputLayer[i].setConnectionsHeights(weights);
    }
    for (size_t i = 0; i < outputLayer.size(); i++)
    {
        values.pop_front();
    }

    if (values.size() != 0)
    {
        std::cerr << "Warning: Possible badly formatted data in \'" << path << "\'";
    }
}
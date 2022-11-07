#include "NN/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::show() const
{
    std::cout << std::setprecision(3);
    std::cout << "------ INPUT LAYER ------" << std::endl;
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

        if (outputLayer[i].getConnectionsHeights().size() <= 0)
        {
            std::cout << "--";
        }
        for (auto h : outputLayer[i].getConnectionsHeights())
        {
            std::cout << "(" << h << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl;
}

void NeuralNetwork::setInputLayer(const InputLayerInfo &layerInfo)
{
    inputLayer = std::vector<Neuron>(layerInfo.qtdNeurons);
}

void NeuralNetwork::setHiddenLayer(const HiddenLayerInfo &layerInfo)
{
    for (auto groupSize : layerInfo.sizesOfNeuronsGroups)
    {
        hiddenLayer.push_back(std::vector<Neuron>(groupSize));
    }
    ACTIVFUNC_HIDDEN = layerInfo.activationFunction;
}

void NeuralNetwork::setOutputLayer(const OutputLayerInfo &layerInfo)
{
    outputLayer = std::vector<Neuron>(layerInfo.qtdNeurons);
    ACTIVFUNC_OUTPUT = layerInfo.activationFunction;
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
    file.close();

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
        inputLayer[i].setBias(values[i][0]);

        std::vector<float> weights;
        for (size_t j = 1; j < values[i].size(); j++)
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
            hiddenLayer[i][j].setBias(values[j][0]);

            std::vector<float> weights;
            for (size_t k = 1; k < values[i].size(); k++)
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
        outputLayer[i].setBias(values[i][0]);

        std::vector<float> weights;
        for (size_t j = 1; j < values[i].size(); j++)
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

void NeuralNetwork::setServerAddress(std::string ip, unsigned short port)
{
    serverIP = ip;
    serverPORT = port;
}

int NeuralNetwork::getCurrentGenerationID() const
{
    return currentGenerationID;
}

int NeuralNetwork::getCurrentGenerationSIZE() const
{
    return currentGenerationSIZE;
}

int NeuralNetwork::getCurrentChromossomeID() const
{
    return currentChromossomeID;
}

void NeuralNetwork::getNewChromossomeFromServer(ServerRequest request)
{
    sf::TcpSocket socket;

    auto res = socket.connect(serverIP, serverPORT);
    if (res == sf::Socket::Done)
    {
        std::cout << "Connected to Genetic Server [" << serverIP << ":" << serverPORT << "]\n";
    } else 
    {
        std::cout << "Connect failed. Address: " << serverIP << ":" << serverPORT << "\n";
    }

    sf::Packet packet;
    packet << request.generationID << request.chromossomeID << request.fitnessValue;

    // Enquanto ele não receber a mensagem, vai ficar enviando requisições
    bool loop = true;
    std::vector<float> genes;
    while (loop)
    {
        res = socket.send(packet);
        if (res != sf::Socket::Done)
        {
            std::cout << "Request not sent! Trying again...\n";
        }

        packet.clear();
        res = socket.receive(packet);
        if (res == sf::Socket::Done)
        {
            loop = false;
        }
        else
        {
            std::cout << "Response not received! Trying again...\n";
        }
    }

    // Salvar IDs de geração e cromossomo atual
    packet >> currentGenerationID >> currentChromossomeID >> currentGenerationSIZE;

    std::cout << "Generation: [" << currentGenerationID << "]   Chromossome: [" << currentChromossomeID << "]\n";

    // Pegar os valores para montar o cromossomo
    float gene = 0;
    while (packet >> gene)
    {
        genes.push_back(gene);
    }

    std::cout << "Data: ";

    for (unsigned int i = 0; i < genes.size(); ++i)
    {
        std::cout << genes[i] << " ";
    }
    std::cout << std::endl;

    // Construir um cromossomo baseado nos valores obtidos do servidor
    Chromosome chromosome;
    chromosome.setAllGenes(genes);
    loadDataFromChromosome(chromosome);

    socket.disconnect();

    // exit(0);
}

// [x]         valor a ser normalizado
// [xMin xMax] variação do valor de x
// [d1 d2]     Limite ao qual o valor de x será reduzido
float NeuralNetwork::normalize(float x, float xMin, float xMax, float d1, float d2)
{
    return (((x - xMin) * (d2 - d1)) / (xMax - xMin)) + d1;
}

std::vector<float> NeuralNetwork::takeDecision(const std::vector<float> &inputParams)
{

    // Preencher Neuronios da camada de entrada com os valores

    for (unsigned int i = 0; i < inputParams.size(); i++)
    {
        inputLayer[i].setValue(inputParams[i], ACTFUNC::NONE);
    }

    // Calcular os valores para a camada oculta

    // Primeiro grupo de neuronios da camada oculta
    for (unsigned int i = 0; i < hiddenLayer[0].size(); i++)
    {
        float result = 0.0;
        for (unsigned int j = 0; j < inputLayer.size(); j++)
        {
            float value = inputLayer[j].getValue();
            float weight = inputLayer[j].getConnectionsHeights()[i];
            float bias = inputLayer[j].getBias();
            result += (value * weight) + bias;
        }
        hiddenLayer[0][i].setValue(result, ACTFUNC::NONE /*activFuncHidden*/);
    }

    // Restante dos grupos de neuronios da camada oculta
    for (unsigned int i = 1; i < hiddenLayer.size(); i++)
    {
        for (unsigned int j = 0; j < hiddenLayer[i].size(); j++)
        {
            float result = 0.0;

            for (unsigned int k = 0; k < hiddenLayer[i - 1].size(); k++)
            {
                float value = hiddenLayer[i - 1][k].getValue();
                float weight = hiddenLayer[i - 1][k].getConnectionsHeights()[j];
                float bias = hiddenLayer[i - 1][j].getBias();
                result += (value * weight) + bias;
            }
            hiddenLayer[i][j].setValue(result, ACTIVFUNC_HIDDEN /*activFuncHidden*/);
        }
    }

    // Preenchimento da camada de saida
    for (unsigned int i = 0; i < outputLayer.size(); i++)
    {
        float result = 0.0;
        for (unsigned int j = 0; j < hiddenLayer[hiddenLayer.size() - 1].size(); j++)
        {
            float value = hiddenLayer[hiddenLayer.size() - 1][j].getValue();
            float weight = hiddenLayer[hiddenLayer.size() - 1][j].getConnectionsHeights()[i];
            float bias = hiddenLayer[hiddenLayer.size() - 1][j].getBias();
            result += (value * weight) + bias;
        }
        outputLayer[i].setValue(result, ACTIVFUNC_OUTPUT /*activFuncOutput*/);
    }

    // Preparar retorno da decisão
    std::vector<float> decision;
    for (Neuron neuron : outputLayer)
    {
        decision.push_back(neuron.getValue());
    }

    return decision;
}

void NeuralNetwork::loadDataFromChromosome(const Chromosome &chromossome)
{
    // Cada cromossomo tem as informaçoes de pesos sinápticos e bias
    // estas informações serão lidas e virão da seguinte maneira (exemplo ilustrativo):
    // bias+pesos_sinapticos+bias+pesos_sinapticos+bias+pesos_sinapticos+

    // calcular tamanho total esperado do cromossomo de acordo com a tolpologia atual da rede neural
    unsigned qtdNeurons = 0;
    unsigned qtdConnections = 0;

    // camada de entrada
    qtdNeurons += inputLayer.size();
    qtdConnections += inputLayer.size() * hiddenLayer[0].size();

    // camada oculta
    qtdNeurons += hiddenLayer[hiddenLayer.size() - 1].size();
    for (unsigned i = 0; i < hiddenLayer.size() - 1; ++i)
    {
        qtdNeurons += hiddenLayer[i].size();
        qtdConnections += hiddenLayer[i].size() * hiddenLayer[i + 1].size();
    }

    // camada de saída
    qtdNeurons += outputLayer.size();
    qtdConnections += hiddenLayer[hiddenLayer.size() - 1].size() * outputLayer.size();

    // Efetuar comparação
    unsigned expectedChromosomeSize = (qtdConnections + qtdNeurons);
    if (expectedChromosomeSize != chromossome.getAllGenes().size())
    {
        std::cerr << "\n[ERROR] Cromossomo incompatível com a topologia da rede neural atual.\n"
                  << "Tamanho esperado: " << expectedChromosomeSize << "   Atual: " << chromossome.getAllGenes().size() << "\n\n";
        exit(-1);
    }

    // Inserindo os valores nas suas respactivas camadas

    // Primeiro, criar um vetor de indices que guardara as posições dos bias;
    // os pesos sinápticos serão coletados entre um bias e outro
    std::deque<unsigned> indexes(1);
    unsigned index = 0;

    // camada de entrada
    unsigned offset = hiddenLayer[0].size();
    for (unsigned int i = 0; i < inputLayer.size(); i++)
    {
        index += offset + 1;
        indexes.push_back(index);
    }

    // camada oculta
    for (unsigned int i = 1; i < hiddenLayer.size(); i++)
    {
        unsigned offset = hiddenLayer[i].size();
        for (unsigned int j = 0; j < hiddenLayer[i - 1].size(); j++)
        {
            index += offset + 1;
            indexes.push_back(index);
        }
    }

    // Camada de saída
    offset = outputLayer.size();
    for (unsigned int i = 0; i < hiddenLayer[hiddenLayer.size() - 1].size(); i++)
    {
        index += offset + 1;
        indexes.push_back(index);
    }

    // Com os indices corretos mapeados, é hora de inserir os valores na rede neural

    // Camada de entrada
    for (unsigned int i = 0; i < inputLayer.size(); i++)
    {
        // pegar os valores dentro do intervalo; primeiro valor bias, restante é peso sináptico
        float bias = chromossome.getGene(indexes[0]);
        std::vector<float> connections;
        for (unsigned int j = indexes[0] + 1; j < indexes[1]; j++)
        {
            connections.push_back(chromossome.getGene(j));
        }
        inputLayer[i].setConnectionsHeights(connections);
        inputLayer[i].setBias(bias);
        indexes.pop_front();
    }

    // camada oculta
    for (unsigned int i = 0; i < hiddenLayer.size(); i++)
    {
        for (unsigned int j = 0; j < hiddenLayer[i].size(); j++)
        {
            // pegar os valores dentro do intervalo; primeiro valor bias, restante é peso sináptico
            float bias = chromossome.getGene(indexes[0]);
            std::vector<float> connections;
            for (unsigned int j = indexes[0] + 1; j < indexes[1]; j++)
            {
                connections.push_back(chromossome.getGene(j));
            }
            hiddenLayer[i][j].setConnectionsHeights(connections);
            hiddenLayer[i][j].setBias(bias);
            indexes.pop_front();
        }
    }

    // camada de saida
    for (unsigned int i = 0; i < outputLayer.size(); i++)
    {
        // A camada de saida não tem conecções, então será setado apenas o bias
        float bias = chromossome.getGene(indexes[0]);
        outputLayer[i].setBias(bias);
        indexes.pop_front();
    }

    // Neste ponto o vetor indexes não terá mais nenhuma valor. se ainda existir algum, aconteceu um erro
    if (!indexes.empty())
    {
        std::cerr << "[ERROR]] Ocorreu um erro na definição de pessos da RN" << std::endl;
    }
}
#include "GeneticServer.h"

GeneticServer::GeneticServer()
{
}

GeneticServer::GeneticServer(Population *population) : population(population)
{
    currentChromossome = population->getCurrentPopulation()[0];
    generationSize = population->getCurrentPopulation().size() - 1;
};

GeneticServer::~GeneticServer()
{
}

void GeneticServer::setPort(unsigned port)
{
    this->port = port;
}

void GeneticServer::next()
{
    // Verificar se todos os cromossomos da geração foram oferecidos para clientes
    if (chromosomeCount == generationSize)
    {
        std::cout << "------ if(chromosomeCount == generationSize) ------\n";
        // Verificar se todos os cromossomos oferecidos já tem um fitness
        // Pode acontecer de um cliente ainda estar testando
        bool generationFullyTested = true;
        for (unsigned i = 0; i < population->getCurrentPopulation().size(); i++)
        {
            if (population->getCurrentPopulation()[i].getFitness() == 0)
            {
                std::cout << "------ generationFullyTested = false; ------\n";
                generationFullyTested = false;
            }
            else
            {
                std::cout << "------ generationFullyTested = true; ------\n";
            }
        }

        if (generationFullyTested)
        {
            std::cout << "------ if(generationFullyTested) ------\n";
            population->generateNewPopulation();
            generationCount++;
            generationSize = population->getCurrentPopulation().size() - 1;
            chromosomeCount = 0;
        }
        return;
    }
    currentChromossome = population->getCurrentPopulation()[++chromosomeCount];
}

void GeneticServer::start()
{
    std::cout << "+-----------------------------------------+\n";
    std::cout << "|   Genetic Server [" << sf::IpAddress::getLocalAddress() << ":" << port << "]  |\n";
    std::cout << "+-----------------------------------------+\n";
    for (;;)
    {
        sf::TcpListener listener;
        listener.listen(port);

        sf::TcpSocket socket;
        auto res = listener.accept(socket);
        if (res != sf::Socket::Done)
        {
            std::cout << "--- Connection failed ---" << std::endl;
        }
        else
        {
            std::cout << "\nClient Connected!" << std::endl;
        }

        sf::Packet packet;

        res = socket.receive(packet);
        if (res != sf::Socket::Done)
        {
            std::cout << "--- Receive failed ---" << std::endl;
        }

        // Recebendo dados do cliente / requisição
        sf::Int32 gen, chrom, fit;
        packet >> gen >> chrom >> fit;

        std::cout << "Request: [" << gen << " " << chrom << " " << fit << "]\nData: ";
        // Independente de ser primeira requisição ou não, sempre será retornado
        // um cromossomo válido para o cliente

        packet.clear();

        // Inserir IDs de geração e população
        packet << generationCount << chromosomeCount << generationSize;

        for (float i : currentChromossome.getAllGenes())
        {
            std::cout << i << " ";
            packet << i;
        }
        std::cout << std::endl;
        socket.send(packet);

        // Requisição com valor válido de IDs e de fitness
        if (gen != -1 && chrom != -1 && fit != -1)
        {
            // Verificar se os valores contidos na requisição se referam a geração atal ou da anterior
            if (gen == generationCount)
            {
                std::cout << "population->setChromossomeFitness(chrom, fit); c: " << chrom << "   f: " << fit << std::endl;
                population->setChromossomeFitness(chrom, fit);
            } else 
            {
                std::cout << "-------- INFORMACAO REFERENTE A UM CROMOSSOMO DA GERACAO ANTERIOR --------\n";
            }
        }

        socket.disconnect();
        listener.close();
        next();
    }
}

void GeneticServer::test()
{

    puts("111");
    sf::TcpSocket socket;

    auto res = socket.connect("localhost", 45001);
    if (res != sf::Socket::Done)
    {
        std::cout << "Connection server not established.\n";
    }

    puts("222");
    sf::Packet packet;

    sf::Int32 a = -1, b = -1, c = -1;
    packet << a << b << c;

    res = socket.send(packet);

    puts("333");
    if (res != sf::Socket::Done)
    {
        std::cout << "Message not sent!\n";
    }

    packet.clear();
    res = socket.receive(packet);
    puts("444");
    std::vector<float> genes;
    if (res != sf::Socket::Done)
    {
        std::cout << "Message not received!\n";
    }

    /*
    std::cout << "Received from server:\n";
    float x = 0;
    packet >> x;
    std::cout << x << "\n";
    */

    for (unsigned int i = 0; i < currentChromossome.getAllGenes().size(); i++)
    {
        float gene = 0;
        packet >> gene;
        genes.push_back(gene);
    }

    std::cout << "Received from server:\n";

    for (unsigned int i = 0; i < genes.size(); ++i)
    {
        std::cout << genes[i] << " ";
    }
    std::cout << std::endl;

    socket.disconnect();
}
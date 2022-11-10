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
        // Voltar o contador para que possa começar do 0 logo em seguida (currentChromossome)
        chromosomeCount = -1;

        // std::cout << "------ if(chromosomeCount == generationSize) ------\n";
        //  Verificar se todos os cromossomos oferecidos já tem um fitness
        //  Pode acontecer de um cliente ainda estar testando
        bool generationFullyTested = true;
        for (unsigned i = 0; i < population->getCurrentPopulation().size(); i++)
        {
            if (population->getCurrentPopulation()[i].getFitness() == 0)
            {
                // std::cout << "------ generationFullyTested = false; ------\n";
                generationFullyTested = false;
            }
            else
            {
                // std::cout << "------ generationFullyTested = true; ------\n";
            }
        }

        if (generationFullyTested)
        {
            // std::cout << "------ if(generationFullyTested) ------\n";
            population->executeElitism();
            population->generateNewPopulation();
            generationCount++;
            generationSize = population->getCurrentPopulation().size() - 1;
        }
        return;
    }

    // Pular todos os cromossomos que contenham valor de fitness
    for (;;)
    {
        currentChromossome = population->getCurrentPopulation()[++chromosomeCount];
        if (currentChromossome.getFitness() == 0)
        {
            break;
        }
    }
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
                population->setChromossomeFitness(chrom, fit);
            }
        }

        socket.disconnect();
        listener.close();
        next();
    }
}

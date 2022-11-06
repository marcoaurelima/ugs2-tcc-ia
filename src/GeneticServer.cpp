#include "GeneticServer.h"

GeneticServer::GeneticServer()
{
}

GeneticServer::GeneticServer(Population *population) : population(population)
{
    currentChromossome = population->getCurrentPopulation()[0];
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
    currentChromossome = population->getCurrentPopulation()[chromosomeCount++];
}

void GeneticServer::start()
{
    std::cout << "Initializing server: [" << sf::IpAddress::getLocalAddress() << ":" << port << "]\n";
    for (;;)
    {
        sf::TcpListener listener;
        listener.listen(port);

        sf::TcpSocket socket;
        auto res = listener.accept(socket);
        if (res != sf::Socket::Done)
        {
            std::cout << "  -Connection failed" << std::endl;
        }
        else
        {
            std::cout << "  -Connected" << std::endl;
        }

        sf::Packet packet;

        res = socket.receive(packet);
        if (res != sf::Socket::Done)
        {
            std::cout << "  -Receive failed" << std::endl;
        }

        // Recebendo dados do cliente / requisição
        sf::Int32 gen, chrom, fit;
        packet >> gen >> chrom >> fit;

        // Valores -1 indicam primeira requisição de instancia do jogo
        if (gen == -1 && chrom == -1 && fit == -1)
        {
            std::cout << "req: " << gen << " " << chrom << " " << fit << "\nData: ";

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
        }

        listener.close();
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
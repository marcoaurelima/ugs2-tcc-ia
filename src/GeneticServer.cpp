#include "GeneticServer.h"

GeneticServer::GeneticServer()
{
}

GeneticServer::GeneticServer(Population *population) : population(population){};

GeneticServer::~GeneticServer()
{
}

void GeneticServer::setPort(unsigned port)
{
    this->port = port;
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
        if (res == sf::Socket::Done)
        {
            std::cout << "  -Connection established" << std::endl;
        }

        sf::Packet packet;

        std::cout << "Recebendo dados...\n";
        res = socket.receive(packet);
        if (res == sf::Socket::Done)
        {
            sf::Uint32 gen, chrom, fit;

            packet >> gen >> chrom >> fit;

            std::cout << gen << " " << chrom << " " << fit << std::endl;
        }

        packet.clear();
        packet << "chromo[1,2,3,4,5]";
        socket.send(packet);
        
        listener.close();
    }
}

void GeneticServer::test()
{
    sf::TcpSocket socket;

    auto res = socket.connect("localhost", 45000);
    if (res == sf::Socket::Done)
    {
        std::cout << "Connection server established.\n";
    }

    sf::Packet packet;

    sf::Uint32 a = 2, b = 44, c = 230;
    packet << a << b << c;

    res = socket.send(packet);

    if (res == sf::Socket::Done)
    {
        std::cout << "Message sent!\n";
    }

    packet.clear();
    res = socket.receive(packet);
    if (res == sf::Socket::Done)
    {
        std::string message;
        packet >> message;
        std::cout << "Received from server: " << message << std::endl;
    }

}
#include "GeneticServer.h"

GeneticServer::GeneticServer()
{
}

GeneticServer::~GeneticServer()
{
}

void GeneticServer::setAddress(std::string address, unsigned port)
{
    this->address = address;
    this->port = port;
}

void GeneticServer::start()
{
    std::cout << "Iniciando server...\n";
    sf::TcpListener listener;
    listener.listen(45000);

    sf::TcpSocket socket;

    std::cout << "Esperando conexoes...\n";
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
        sf::Uint32 a, b, c;

        packet >> a >> b >> c;

        std::cout << a << " " << b << " " << c << std::endl;
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

    sf::Uint32 a=2, b=44, c=230;
    packet << a << b << c;

    res = socket.send(packet);

    if (res == sf::Socket::Done)
    {
        std::cout << "Message sent!\n";
    }
}
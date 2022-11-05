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
    if(res == sf::Socket::Done)
    {
        std::cout << "  -Connection established" << std::endl;
    }

    const std::size_t size = 100;
    char data[size];
    std::size_t readSize = 0;

    std::cout << "Recebendo dados...\n";
    res = socket.receive(data, size, readSize);
    if(res == sf::Socket::Done)
    {
        std::cout << "  -Received " << readSize << " bytes from client." << std::endl;
    }

    std::cout << "  -Data: " << data << "\n";


}

void GeneticServer::test()
{
    sf::TcpSocket socket;

    auto res = socket.connect("localhost", 45000);
    if(res == sf::Socket::Done)
    {
        std::cout << "Connection server established.\n";
    }

    const int msgSize = 100;
    char msg[msgSize] = "Testando conexao!\n";

    res = socket.send(msg, msgSize);
    if(res == sf::Socket::Done)
    {
        std::cout << "Message sent!\n";
    }

}
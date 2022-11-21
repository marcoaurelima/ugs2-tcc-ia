#include "GeneticServer.h"

GeneticServer::GeneticServer()
{
}

GeneticServer::GeneticServer(Population *population) : population(population)
{
    currentChromossome = population->getCurrentPopulation()[0];
    generationSize = population->getCurrentPopulation().size() - 1;

    sentControl = std::vector<bool>(static_cast<unsigned>(generationSize + 1));
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
    // Geração foi completamente entregue
    bool generationFullySent = true;

    //  Pular todos os cromossomos que contenham valor de fitness
    for (unsigned i = 0; i < sentControl.size(); i++)
    {
        // Ainda não foi enviado
        if (sentControl[i] == false)
        {
            // puts("***");
            if (population->getCurrentPopulation()[i].getFitness() == 0)
            {
                sentControl[i] = true;
                generationFullySent = false;
                currentChromossome = population->getCurrentPopulation()[i];
                chromosomeCount = i;
                break;
            }
        }
    }

    if (generationFullySent)
    {
        puts("generationFullySent!!!\n");

        // Verificar se a geração inteira já tem fitness; Se não tiver, começar a entrega
        // de cromossomos que faltam para novos clientes
        bool generationFullyTested = true;
        for (unsigned i = 0; i < population->getCurrentPopulation().size(); i++)
        {
            if (population->getCurrentPopulation()[i].getFitness() == 0)
            {
                std::cout << "\n--- Indice [" << i << "] ainda nao tem fitness. ---\n";
                generationFullyTested = false;
            }
        }

        if (!generationFullyTested)
        {
            sentControl = std::vector<bool>(static_cast<unsigned>(generationSize + 1));
            return;
        }

        std::cout << "---  generationFullyTested  ---\n";
        population->executeElitism();
        population->generateNewPopulation();
        generationCount++;
        generationSize = population->getCurrentPopulation().size() - 1;

        sentControl = std::vector<bool>(static_cast<unsigned>(generationSize) + 1);
    }
}

void GeneticServer::_next()
{
    // Verificar se todos os cromossomos da geração foram oferecidos para clientes
    if (chromosomeCount == generationSize)
    {
        // Voltar o contador para que possa começar do 0 logo em seguida (currentChromossome)
        /// chromosomeCount = -1;

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
    std::cout << "+------------------------------------------------------------+\n";
    std::cout << "|   Genetic Server [selector-version] [" << sf::IpAddress::getLocalAddress() << ":" << port << "]  |\n";
    std::cout << "+------------------------------------------------------------+\n";

    sf::TcpListener listener;
    listener.listen(port);
    std::list<sf::TcpSocket *> clients;

    sf::SocketSelector selector;

    selector.add(listener);
    for (;;)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket *client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(client);
                    selector.add(*client);
                }
                else
                {
                    delete client;
                }
            }
            else
            {
                for (std::list<sf::TcpSocket *>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket &client = **it;
                    if (selector.isReady(client))
                    {
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
                            // Recebendo dados do cliente / requisição
                            sf::Int32 gen, chrom, fit;
                            packet >> gen >> chrom >> fit;

                            // Salvando os logs
                            saveLogs(gen, chrom, fit);

                            if (fit > bestFit)
                            {
                                bestFit = fit;
                            }

                            std::cout << "\n--- Best fit: [" << bestFit << "]\n";
                            std::cout << "\nRequest: [" << gen << " " << chrom << " " << fit << "]\n";
                            // Independente de ser primeira requisição ou não, sempre será retornado
                            // um cromossomo válido para o cliente

                            packet.clear();

                            // Inserir IDs de geração e população
                            packet << generationCount << chromosomeCount << generationSize;

                            for (float i : currentChromossome.getAllGenes())
                            {
                                // std::cout << i << " ";
                                packet << i;
                            }
                            //std::cout << std::endl;
                            client.send(packet);

                            // Requisição com valor válido de IDs e de fitness
                            if (gen != -1 && chrom != -1 && fit != -1)
                            {
                                // Verificar se os valores contidos na requisição se referam a geração atal ou da anterior
                                if (gen == generationCount)
                                {
                                    population->setChromossomeFitness(chrom, fit);
                                }
                            }

                            // client.disconnect();
                            // listener.close();
                            next();
                        }
                    }
                }
            }
        }
    }

    /*for (;;)
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
    }*/
}

void GeneticServer::saveLogs(int gen, int chrom, int fit) const
{
    if (gen == -1 || chrom == -1 || fit == -1)
    {
        return;
    }

    std::time_t result = std::time(nullptr);
    std::string now(std::ctime(&result));

    std::stringstream filename;
    filename << "logs/chromossomes/"
             << "F-" << fit
             << " G-" << gen
             << " C-" << chrom
             << " - " << now.substr(0, now.size() - 1)
             << ".log";

    std::stringstream fileContents;

    unsigned index = chrom;
    for (unsigned i = 0; i < population->getCurrentPopulation()[index].getAllGenes().size(); i++)
    {
        fileContents << population->getCurrentPopulation()[index].getAllGenes()[i] << ", ";
    }

    std::string filenameCorr;
    for (unsigned i = 0; i < filename.str().size(); i++)
    {
        if (filename.str()[i] == ' ')
        {
            filenameCorr += R"(   )";
            continue;
        }
        else if (filename.str()[i] == ':')
        {
            filenameCorr += '-';
            continue;
        }

        filenameCorr += filename.str()[i];
    }

    std::ofstream file;
    file.open(filenameCorr, std::ofstream::out);
    if (!file.is_open())
    {
        std::cerr << "Error: " << filenameCorr << std::endl;
    }

    file << fileContents.str();
    file.close();

    FILE *fileFit = fopen("logs/fitness-log.txt", "a");
    fprintf(fileFit, "%d\n", fit);
    fclose(fileFit);

    fileFit = fopen("logs/best-fitness.txt", "w");
    fprintf(fileFit, "%d\n", bestFit);
    fclose(fileFit);
}

void GeneticServer::_start()
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

        std::cout << "Request: [" << gen << " " << chrom << " " << fit << "]\n";
        // Independente de ser primeira requisição ou não, sempre será retornado
        // um cromossomo válido para o cliente

        packet.clear();

        // Inserir IDs de geração e população
        packet << generationCount << chromosomeCount << generationSize;

        for (float i : currentChromossome.getAllGenes())
        {
            // std::cout << i << " ";
            packet << i;
        }
        // std::cout << std::endl;
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

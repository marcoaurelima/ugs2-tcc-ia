#include "GA/Population.h"

Population::Population() {}

Population::~Population() {}

float Population::getRandomFloat()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 10.0);

    return dist(mt);
}

void Population::createInitialPopulation(const unsigned populationSize, const unsigned chromossomeSize)
{
    for (size_t i = 0; i < populationSize; i++)
    {
        Chromosome c;
        for (size_t j = 0; j < chromossomeSize; j++)
        {
            float randFloat = getRandomFloat();
            c.setGene(randFloat);
        }
        // c.setRandomFitness();
        chromosomes.push_back(c);
    }
}

void debugNumber(int number)
{
    for (int i = 0; i < 20; i++)
        std::cout << number << " ";
    std::cout << "\n";
}

void Population::show() const
{
    std::cout << "------------------------------- Population: ------------------------------- " << std::endl;
    for (auto &c : chromosomes)
    {
        c.show();
    }
    std::cout << "---------------------------------------------------------------------------\n\n"
              << std::endl;
}

void Population::setNewGenerationParams(const NewGenParams newGenParams)
{
    this->newGenParams = newGenParams;
}

void Population::generateNewPopulation()
{
    /// seleção ///
    switch (newGenParams.selectionType)
    {
    case SELECTION_TYPE::FITNESS:
        std::cout << "ETAPA: Selection    MÉTODO: Fitness" << std::endl;
        break;
    case SELECTION_TYPE::TOURNAMENT:
        std::cout << "ETAPA: Selection    MÉTODO: Tournament" << std::endl;
        break;
    case SELECTION_TYPE::ROULLETE:
        std::cout << "ETAPA: Selection    MÉTODO: Roullete" << std::endl;
        selectionRoulette();
        break;
    case SELECTION_TYPE::STOCHASTIC_US:
        std::cout << "ETAPA: Selection    MÉTODO: Stochastic Universal Sampling" << std::endl;
        selectionEstocastic();
        break;
    default:
        break;
    }

    /// cruzamento ///
    switch (newGenParams.crossoverType)
    {
    case CROSSOVER_TYPE::SINGLE_POINT:
        std::cout << "ETAPA: Crossover    MÉTODO: Single-Point" << std::endl;
        crossoverSinglePoint();
        break;
    case CROSSOVER_TYPE::MULTI_POINT:
        std::cout << "ETAPA: Crossover    MÉTODO: Multi-Point MULTI_POINT" << std::endl;
        break;
    case CROSSOVER_TYPE::UNIFORM:
        std::cout << "ETAPA: Crossover    MÉTODO: Uniform" << std::endl;
        crossoverUniform();
        break;
    default:
        break;
    }

    /// mutação ///
    switch (newGenParams.mutationType)
    {
    case MUTATION_TYPE::INSERTION:
        std::cout << "ETAPA: Mutation    MÉTODO: Inserção" << std::endl;
        mutationInsertion();
        break;
    case MUTATION_TYPE::INVERSION:
        std::cout << "ETAPA: Mutation    MÉTODO: Inverção" << std::endl;
        break;
    case MUTATION_TYPE::UNIFORM:
        std::cout << "ETAPA: Mutation    MÉTODO: Uniform" << std::endl;
        mutationUniform();
        break;
    default:
        break;
    }
}

std::vector<unsigned> Population::getConfig(const std::string &path) const
{
    std::ifstream stream(path);
    if (!stream.is_open())
    {
        std::cout << "ERROR: configuration \"" << path << "\" not found." << std::endl;
    }
    std::vector<unsigned> values;
    std::string v;
    while (stream >> v)
    {
        values.push_back(std::stoi(v));
    }

    return values;
}

// fitness: vetor com todos os fitness que estarao na roleta
// qtdNidles: quantidade de agulhas na roleta
// spin: giro da roleta; porcentagem do giro 1% - 99%
void Population::selectionEstocastic(int qtdNidles)
{
    // Se não for definido uma quantidade por parametro, este será lido no arquivo de conf.
    if (qtdNidles == 0)
    {
        qtdNidles = getConfig("configurations/GA/selection/estocastic/qtdneedles")[0];
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 99);

    const unsigned spin = dist(mt);

    float fitnessSum = 0;
    for (Chromosome &c : chromosomes)
    {
        fitnessSum += c.getFitness();
    }

    // Produzir um vetor de aprox. de 100 posições (valores float as vezes somam 99% no total),
    // onde terão vários blocos de valores repetidos representando as fatias da roleta.
    // cada bloco conterá o indice do cromossomo. Ex.: 001111222
    // No caso acima, o fitness na posição 2 tem uma fatia maior, enquanto o 0 tem a menor.

    std::vector<unsigned> percents;
    for (unsigned i = 0; i < chromosomes.size(); i++)
    {
        unsigned value = (chromosomes[i].getFitness() / fitnessSum) * 100;
        percents.push_back(value);
    }

    // Preencher a roleta com blocos de valores

    std::deque<unsigned> roulette{};
    for (unsigned int i = 0; i < percents.size(); i++)
    {
        for (unsigned j = 0; j < percents[i]; j++)
        {
            roulette.push_back(i);
        }
    }

    /// girar a roleta

    for (unsigned i = 0; i < spin; i++)
    {
        roulette.push_back(roulette[i]);
    }
    for (unsigned i = 0; i < spin; i++)
    {
        roulette.pop_front();
    }

    // Calcular indices das agulhas em relação a roleta

    std::vector<unsigned> indexNidles{};
    for (size_t i = 0; i < static_cast<size_t>(qtdNidles); i++)
    {
        unsigned index = ((100 / qtdNidles) * i) + ((100 / qtdNidles) / 2);
        indexNidles.push_back(index);
    }

    // Efetuar seleção dos indices dos cromossomos que as agulhas apontam

    std::set<unsigned> selectionIndexes{};
    for (unsigned &i : indexNidles)
    {
        selectionIndexes.insert(roulette[i]);
    }

    std::vector<Chromosome> chromosomesTEMP = chromosomes;
    chromosomes.clear();

    for (const unsigned &i : selectionIndexes)
    {
        chromosomes.push_back(chromosomesTEMP[i]);
    }

    std::cout << "qtdNidles " << qtdNidles << "    ";
    std::cout << "indexNidles ";
    for (auto &i : indexNidles)
    {
        std::cout << i << " ";
    }
    std::cout << "   ";
    std::cout << "spin " << spin << std::endl;
    std::cout << "selectionIndexes ";
    for (auto &i : selectionIndexes)
    {
        std::cout << "[" << i << "] ";
    }
    std::cout << "    \n";

    std::cout << "Population size [initial: " << chromosomesTEMP.size() << "] - [final: " << chromosomes.size() << ']' << std::endl;
    show();
}

// Roleta: mesmo algorítmo do estocastico, so que com apenas 1 agulha
void Population::selectionRoulette()
{
    unsigned qtdTurns = getConfig("configurations/GA/selection/roullete/qtdturns")[0];
    std::cout << "qtdTurns: " << qtdTurns << std::endl;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 99);

    // Efetuar a quantidade de turnos definida; em cada turno guardar o indice escolhido.
    // Estes indices serão guardados no set para evitar repetidos.

    std::set<unsigned> indexesSelection;

    std::cout << "Selection: ";
    for (size_t i = 0; i < qtdTurns; i++)
    {
        const unsigned spin = dist(mt);

        float fitnessSum = 0;
        for (Chromosome &c : chromosomes)
        {
            fitnessSum += c.getFitness();
        }

        // Produzir um vetor de aprox. de 100 posições (valores float as vezes somam 99% no total),
        // onde terão vários blocos de valores repetidos representando as fatias da roleta.
        // cada bloco conterá o indice do cromossomo. Ex.: 001111222
        // No caso acima, o fitness na posição 2 tem uma fatia maior, enquanto o 0 tem a menor.

        std::vector<unsigned> percents;
        for (unsigned i = 0; i < chromosomes.size(); i++)
        {
            unsigned value = (chromosomes[i].getFitness() / fitnessSum) * 100;
            percents.push_back(value);
        }
        // Preencher a roleta com blocos de valores

        std::deque<unsigned> roulette{};
        for (unsigned int i = 0; i < percents.size(); i++)
        {
            for (unsigned j = 0; j < percents[i]; j++)
            {
                roulette.push_back(i);
            }
        }

        /// girar a roleta

        for (unsigned i = 0; i < spin; i++)
        {
            roulette.push_back(roulette[i]);
        }
        for (unsigned i = 0; i < spin; i++)
        {
            roulette.pop_front();
        }

        // A agulha está definida para ser estática na posição 0 da roleta
        indexesSelection.insert(roulette[0]);
        std::cout << "[" << roulette[0] << "] ";
    }

    std::vector<Chromosome> chromosomesTEMP = chromosomes;
    chromosomes.clear();

    for (auto i : indexesSelection)
    {
        chromosomes.push_back(chromosomesTEMP[i]);
    }

    std::cout << "\nPopulation size [initial: " << chromosomesTEMP.size() << "] - [final: " << chromosomes.size() << ']' << std::endl;
    show();
}

// No cruzamento, serão selecionados pares de cromossomos:
// Por exemplo, em um vetor de 4 cromossomos, o cruzamento será de
// (0,1) e (2,3). Em caso de impares, o ultimo cruzará com um cromossomo aleatório do votor.
void Population::crossoverUniform()
{
    const unsigned taxParent1 = getConfig("configurations/GA/crossover/uniform/contrib")[0];
    const unsigned taxParent2 = getConfig("configurations/GA/crossover/uniform/contrib")[1];
    std::cout << "taxParent1 " << taxParent1 << "%    "
              << "taxParent2 " << taxParent2 << "%" << std::endl;
    std::cout << "masks ";

    // verificar se o vetor de cromossomos tem mais de 1 cromossomo
    if (chromosomes.size() < 2)
        return;

    // verificar se o vetor de cromossomos tem uma quantidade impar
    if (chromosomes.size() % 2 == 1)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, chromosomes.size() - 1);

        // se tiver, selecionar um cromossomo aleatorio e inserir no final

        unsigned index = dist(mt);
        chromosomes.push_back(chromosomes[index]);
    }

    std::vector<Chromosome> chromosomeTEMP = chromosomes;
    chromosomes.clear();

    for (size_t i = 0; i < chromosomeTEMP.size(); i += 2)
    {
        Chromosome parent1 = chromosomeTEMP[i];
        Chromosome parent2 = chromosomeTEMP[i + 1];
        Chromosome child{};

        if (parent1.getAllGenes().size() != parent1.getAllGenes().size())
        {
            std::cerr << "Error: parent1 and parent2 must have the same size." << std::endl;
        }

        if (taxParent1 + taxParent2 != 100)
        {
            std::cerr << "Error: Invalid number of taxParent1." << std::endl;
        }

        size_t chromossomeSize = (parent1.getAllGenes().size() + parent2.getAllGenes().size()) / 2;
        unsigned parent1size = (chromossomeSize * taxParent1) / 100;
        unsigned parent2size = chromossomeSize - parent1size;

        // Produzir a mascara binária;
        // Será gerado trues de acordo com a porcentagem do pai 1;
        // Será gerado falses com a quantidade que faltar para completar a mascara;

        std::vector<bool> mask{};
        for (size_t i = 0; i < parent1size; i++)
        {
            mask.push_back(true);
        }
        for (size_t i = 0; i < parent2size; i++)
        {
            mask.push_back(false);
        }

        // Embaralhar mascara de forma aleatória

        std::random_device randDevice{};
        std::default_random_engine randEngine{randDevice()};
        std::shuffle(std::begin(mask), std::end(mask), randEngine);

        // Efetuar cruzamento a partir da mascara

        for (size_t i = 0; i < mask.size(); i++)
        {
            if (mask[i] == false)
            {
                child.setGene(parent1.getGene(i));
            }
            else
            {
                child.setGene(parent2.getGene(i));
            }
        }

        chromosomes.push_back(child);

        for (auto i : mask)
        {
            std::cout << i;
        }
        std::cout << "    ";
    }

    std::cout << std::endl;

    show();
}

void Population::crossoverSinglePoint(int indexPointDivision)
{
    // Se não for passado um indice válido por parametro, será gerado um válido aleatório.
    if (indexPointDivision == -1)
    {
        const unsigned SIZE = chromosomes[0].getAllGenes().size();
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> dist(0, SIZE - 1);
        indexPointDivision = dist(mt);

        // Evitar que o ponto seja o indice máximo do cromossomo.
        // Se o o indice for esse, não haverá cruzamento pois a primeira parte da
        // divisão do cromossomo tem tamanho igual ao tamanho dele.
        while (indexPointDivision < 1)
        {
            indexPointDivision = dist(mt);
        }
    }

    std::cout << "indexPointDivision " << indexPointDivision << std::endl;

    // Efetuar cruzamento da população
    std::vector<Chromosome> chromosomesTEMP = chromosomes;
    for (unsigned i = 0; i < chromosomes.size(); i++)
    {
        for (unsigned j = i; j < chromosomesTEMP.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            const Chromosome &parent1 = chromosomesTEMP[i];
            const Chromosome &parent2 = chromosomesTEMP[j];

            Chromosome child;

            for (int i = 0; i < indexPointDivision; i++)
            {
                child.setGene(parent1.getGene(i));
            }

            for (unsigned i = indexPointDivision; i < parent2.getSize(); i++)
            {
                child.setGene(parent2.getGene(i));
            }
            chromosomes.push_back(child);
        }
    }

    std::cout << "Population size [initial: " << chromosomesTEMP.size() << "] - [final: " << chromosomes.size() << ']' << std::endl;

    show();
}

// Efetuar mutações na população atual
// Cada mutação será um novo indivíduo no vetor
// Estas mutações ocorrerão seguindo uma probabilidade aleatória
void Population::mutationInsertion()
{
    unsigned probability = getConfig("configurations/GA/mutation/insertion/probability")[0];
    std::cout << "Ocorrency probability: " << probability << "%   \n";

    std::vector<bool> range(100);
    for (unsigned i = 0; i < probability; i++)
    {
        range[i] = true;
    }

    unsigned count = 0;
    std::vector<Chromosome> chromosomesTEMP = chromosomes;
    for (unsigned i = 0; i < chromosomesTEMP.size(); ++i)
    // for(Chromosome& c : chromosomes)
    {
        // Calcular probabilidade (porcentagens inteiras ex.: 1%)

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> dist(0, 100);

        int randIndex = dist(mt);
        bool makeMutation = !(range[randIndex]);
        if (makeMutation)
        {
            std::cout << "[" << i << "|N/M]\t";
            continue;
        }
        else
        {
            std::cout << "[" << i << "|ok]\t";
        }

        unsigned chromosomeSize = chromosomesTEMP[i].getSize();

        std::uniform_int_distribution<unsigned> dist2(0, chromosomeSize - 1);
        unsigned index1 = 0, index2 = 0;
        while (index1 == index2)
        {
            index1 = dist2(mt);
            index2 = dist2(mt);
        }

        // Ordenar indices - index1 deve conter menor valor dos dois

        if (index1 > index2)
        {
            unsigned temp = index1;
            index1 = index2;
            index2 = temp;
        }

        Chromosome mutation{};

        // Salvar valor de (index1) para variavel (auxiliar)
        // Copiar para mutation os valores até (index2)-1, pulando o valor de (index1)
        // Inserir valor de (auxiliar) em (index2)-1
        // Copiar para mutation os valores restantes a partir de (index2)

        float aux = chromosomesTEMP[i].getGene(index1);

        for (size_t k = 0; k < index2; k++)
        {
            if (k == index1)
            {
                continue;
            }
            mutation.setGene(chromosomesTEMP[i].getGene(k));
        }

        mutation.setGene(aux);

        for (size_t k = index2; k < chromosomeSize; k++)
        {
            mutation.setGene(chromosomesTEMP[i].getGene(k));
        }

        chromosomes.push_back(mutation);

        count++;
    }

    std::cout << "\nPopulation size [initial: " << chromosomesTEMP.size() << "] - [final: " << chromosomes.size() << ']' << std::endl;

    show();
}

void Population::mutationUniform(const float MIN_VALUE, const float MAX_VALUE)
{
    unsigned probability = getConfig("configurations/GA/mutation/uniform/probability")[0];
    probability = 50;
    std::cout << "Ocorrency probability: " << probability << "%   \n";

    // Calcular probabilidade (porcentagens inteiras ex.: 1%)
    // Ficará separado de acordo com a prob. Ex.: 1111100000 -> 50%
    std::vector<bool> range(100);
    for (unsigned int i = 0; i < probability; ++i)
    {
        range[i] = true;
    }

    unsigned count = 0;
    std::vector<Chromosome> chromosomesTEMP = chromosomes;
    for (unsigned i = 0; i < chromosomesTEMP.size(); ++i)
    {

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> dist(0, 100);

        int randIndex = dist(mt);
        bool makeMutation = !(range[randIndex]);
        if (makeMutation)
        {
            std::cout << "[" << i << "|N/M]\t";
            continue;
        }
        else
        {
            std::cout << "[" << i << "|ok]\t";
        }

        // Gerar um valor válido e inserir em um indice aleatório

        std::uniform_real_distribution<float> dist3(MIN_VALUE, MAX_VALUE);
        float valueToInsert = dist3(mt);

        std::uniform_int_distribution<unsigned> dist4(0, chromosomesTEMP.size() - 1);
        unsigned index = dist4(mt);

        Chromosome mutation = chromosomes[i];
        mutation.changeGene(index, valueToInsert);
        chromosomes.push_back(mutation);

        count++;
    }

    std::cout << "\ncount: " << count << std::endl;
    std::cout << "chromosomesTEMP size: " << chromosomesTEMP.size() << std::endl;
    std::cout << "chromosomesNEWSIZE: " << chromosomes.size() << std::endl;
    std::cout << std::endl;

    show();
}

std::vector<Chromosome> Population::getCurrentPopulation() const
{
    return chromosomes;
}

void Population::setChromossomeFitness(const unsigned index, const float fitness)
{
    chromosomes[index].setFitness(fitness);
}

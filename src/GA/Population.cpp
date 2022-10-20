#include "GA/Population.h"

Population::Population()
{
    srand(time(NULL));
}

Population::~Population() {}

unsigned Population::getRecordFitness() const
{
    return recordFitness;
}
int Population::generateRandomInt(const int min, const int max)
{
    int number = ((rand() % (max - min)) + min);
    return number;
}

float Population::generateRandomFloat(const float min, const float max)
{
    int iMin = (int)(min * 1000);
    int iMax = (int)(max * 1000);
    float number(((float)((rand() % (iMin - iMax)) + min)) / 1000);
    return number;
}

void Population::shuffleVector(std::vector<bool> &vec)
{
    for (unsigned i = 0; i < vec.size() * 2; i++)
    {
        unsigned j = generateRandomInt(0, vec.size());
        unsigned k = generateRandomInt(0, vec.size());
        bool temp = vec[j];
        vec[j] = vec[k];
        vec[k] = temp;
    }
}

void Population::shuffleChromossomes(std::vector<Chromosome> &chr)
{
    for (unsigned i = 0; i < chr.size() * 2; i++)
    {
        unsigned j = generateRandomInt(0, chr.size());
        unsigned k = generateRandomInt(0, chr.size());
        Chromosome temp = chr[j];
        chr[j] = chr[k];
        chr[k] = temp;
    }
}

void Population::createInitialPopulation(const unsigned populationSize, const unsigned chromossomeSize)
{
    initialPopulationSize = populationSize;

    srand(time(NULL));
    for (size_t i = 0; i < populationSize; i++)
    {
        Chromosome c;
        for (size_t j = 0; j < chromossomeSize; j++)
        {
            float min = 0, max = 0.35;//0.6;
            float randFloat = generateRandomFloat(min, max);
            c.setGene(randFloat);
        }
        // unsigned fitness = generateRandomInt(0, 10000);
        // c.setFitness(fitness);
        chromosomes.push_back(c);
    }
}

void debugNumber(int number)
{
    for (int i = 0; i < 20; i++)
        std::cout << number << " ";
    std::cout << "\n";
}

unsigned Population::getInitialPopulationSize() const
{
    return initialPopulationSize;
}

void Population::show() const
{
    return;

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
    /// executeElitism();

    /// seleção ///
    switch (newGenParams.selectionType)
    {
    case SELECTION_TYPE::FITNESS:
        if (enabledLogs)
            std::cout << "STEP: Selection    METHOD: Fitness" << std::endl;
        break;
    case SELECTION_TYPE::TOURNAMENT:
        if (enabledLogs)
            std::cout << "STEP: Selection    METHOD: Tournament" << std::endl;
        break;
    case SELECTION_TYPE::ROULLETE:
        if (enabledLogs)
            std::cout << "STEP: Selection    METHOD: Roullete" << std::endl;
        selectionRoulette();
        break;
    case SELECTION_TYPE::STOCHASTIC_US:
        if (enabledLogs)
            std::cout << "STEP: Selection    METHOD: Stochastic Universal Sampling" << std::endl;
        selectionEstocastic();
        break;
    default:
        break;
    }

    /// cruzamento ///
    switch (newGenParams.crossoverType)
    {
    case CROSSOVER_TYPE::SINGLE_POINT:
        if (enabledLogs)
            std::cout << "STEP: Crossover    METHOD: Single-Point" << std::endl;
        crossoverSinglePoint();
        break;
    case CROSSOVER_TYPE::MULTI_POINT:
        if (enabledLogs)
            std::cout << "STEP: Crossover    METHOD: Multi-Point" << std::endl;
        break;
    case CROSSOVER_TYPE::UNIFORM:
        if (enabledLogs)
            std::cout << "STEP: Crossover    METHOD: Uniform" << std::endl;
        crossoverUniform();
        break;
    default:
        break;
    }

    /// mutação ///
    switch (newGenParams.mutationType)
    {
    case MUTATION_TYPE::INSERTION:
        if (enabledLogs)
            std::cout << "STEP: Mutation    METHOD: Insertion" << std::endl;
        mutationInsertion();
        break;
    case MUTATION_TYPE::INVERSION:
        if (enabledLogs)
            std::cout << "STEP: Mutation    METHOD: Inversion" << std::endl;
        break;
    case MUTATION_TYPE::UNIFORM:
        if (enabledLogs)
            std::cout << "STEP: Mutation    METHOD: Uniform" << std::endl;
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
    stream.close();

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
        qtdNidles = initialPopulationSize;
    }

    // Eu comecei com precisão de 100, mas não é suficiente.
    // Definirei a precisão em 10000

    const unsigned spin = generateRandomInt(1, 9999);

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
        unsigned value = (chromosomes[i].getFitness() / fitnessSum) * 10000;
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
        unsigned index = ((10000 / qtdNidles) * i) + ((10000 / qtdNidles) / 2);
        indexNidles.push_back(index);
    }

    // Efetuar seleção dos indices dos cromossomos que as agulhas apontam

    std::vector<unsigned> selectionIndexes{};
    for (unsigned &i : indexNidles)
    {
        selectionIndexes.push_back(roulette[i]);
    }

    // std::vector<Chromosome> chromosomesTEMP = chromosomes;
    // chromosomes.clear();

    chromosomesSelected.clear();
    for (const unsigned &i : selectionIndexes)
    {
        chromosomesSelected.push_back(chromosomes[i]);
    }

    if (enabledLogs)
    {
        std::cout << "qtdNidles " << qtdNidles << "    ";
        std::cout << "indexNidles ";
        for (auto &i : indexNidles)
        {
            std::cout << i << " ";
        }
        std::cout << "   ";
        // std::cout << "spin " << spin << std::endl;
        std::cout << "selectionIndexes ";
        for (auto &i : selectionIndexes)
        {
            std::cout << "[" << i << "] ";
        }
        std::cout << "    \n";

        std::cout << "\nSelectioned size [total: " << chromosomes.size() << "] - [select: " << chromosomesSelected.size() << ']' << std::endl;
        show();
    }

    std::cout << "\n\n[selec.estoc] Selectioned size [" << chromosomesSelected.size() << "]\n\n";
}

// Roleta: mesmo algorítmo do estocastico, so que com apenas 1 agulha
// Manter o vetor de cromossomos atual e atualizar o vetor de cromossomos selecionados para efetuar cruzamento e mutação
// depois de definido esse vetor auxiliar, concatenar com o vetor oficial
void Population::selectionRoulette()
{
    unsigned qtdTurns = initialPopulationSize; // getConfig("configurations/GA/selection/roullete/qtdturns")[0];
    if (enabledLogs)
        std::cout << "qtdTurns: " << qtdTurns << std::endl;

    // Efetuar a quantidade de turnos definida; em cada turno guardar o indice escolhido.
    // Estes indices serão guardados no set para evitar repetidos.

    std::vector<unsigned> indexesSelection;

    if (enabledLogs)
        std::cout << "Selection: ";

    for (size_t i = 0; i < qtdTurns; i++)
    {
        const unsigned spin = generateRandomInt(1, 9999);

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
            unsigned value = (chromosomes[i].getFitness() / fitnessSum) * 10000;
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
        // std::cout << "spin " << spin << std::endl;
        for (unsigned i = 0; i < spin; i++)
        {
            roulette.push_back(roulette[i]);
        }
        for (unsigned i = 0; i < spin; i++)
        {
            roulette.pop_front();
        }

        // A agulha está definida para ser estática na posição 0 da roleta
        indexesSelection.push_back(roulette[0]);
        if (enabledLogs)
            std::cout << "[" << roulette[0] << "] ";
    }

    // std::vector<Chromosome> chromosomesTEMP = chromosomes;
    chromosomesSelected.clear();

    for (auto i : indexesSelection)
    {
        chromosomesSelected.push_back(chromosomes[i]);
        // std::cout << "indexesSelection: " << i << std::endl;
    }

    // resetar valor de fitness dos cromossomos seleconados
    for(unsigned i = 0; i < chromosomesSelected.size(); i++)
    {
        chromosomesSelected[i].setFitness(0);
        chromosomesSelected[i].resetFitness();
    }
    
    if (enabledLogs)
    {
        std::cout << "\nSelectioned size [total: " << chromosomesSelected.size() << "]";
        show();
    }

    std::cout << "\n\n[selec.roulle] Selectioned size [" << chromosomesSelected.size() << "]\n\n";
}

// No cruzamento, serão selecionados pares de cromossomos:
// Por exemplo, em um vetor de 4 cromossomos, o cruzamento será de
// (0,1) e (2,3). Em caso de impares, o ultimo cruzará com um cromossomo aleatório do votor.
void Population::crossoverUniform()
{
    const unsigned taxParent1 = getConfig("configurations/GA/crossover/uniform/contrib")[0];
    const unsigned taxParent2 = getConfig("configurations/GA/crossover/uniform/contrib")[1];

    const unsigned probability = getConfig("configurations/GA/crossover/uniform/probability")[0];

    if (enabledLogs)
    {
        std::cout << "taxParent1 " << taxParent1 << "%    "
                  << "taxParent2 " << taxParent2 << "%    "
                  << "Probability " << probability << "%" << std::endl;
        std::cout << "masks ";
    }

    // verificar se o vetor de cromossomos tem mais de 1 cromossomo
    if (chromosomesSelected.size() < 2)
    {
        return;
    }

    // verificar se vetor de cromossomos tem quantidade impar
    // se for, selecionar algum cromossomo aleatorio do mesmo vetor e colocar no final
    if (chromosomesSelected.size() % 2 == 1)
    {
        chromosomesSelected.push_back(chromosomesSelected[generateRandomInt(0, chromosomesSelected.size() - 1)]);
    }

    std::vector<Chromosome> chromosomesSelectedTEMP = chromosomesSelected;
    chromosomesSelected.clear();
    for (size_t i = 0; i < chromosomesSelectedTEMP.size(); i += 2)
    {
        // Decidir se o cruzamento altual ocorerá de acordo com a probabilidade
        if (!getDecisionProb(probability))
        {
            continue;
            std::cout << "[Cruz.Rec|" << i << "] ";
        }

        Chromosome parent1 = chromosomesSelectedTEMP[i];
        Chromosome parent2 = chromosomesSelectedTEMP[i + 1];
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
        shuffleVector(mask);

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

        chromosomesSelected.push_back(child);

        if (enabledLogs)
        {
            for (auto i : mask)
            {
                std::cout << i;
            }
            std::cout << "    ";
        }
    }

    if (enabledLogs)
    {
        std::cout << std::endl;

        show();
    }

    std::cout << "\n\n[cros.uni] Selectioned size [" << chromosomesSelected.size() << "]\n\n";
}

void Population::crossoverSinglePoint(int indexPointDivision)
{
    // Se não for passado um indice válido por parametro, será gerado um válido aleatório.
    if (indexPointDivision == -1)
    {
        const unsigned SIZE = chromosomes[0].getAllGenes().size();

        indexPointDivision = generateRandomInt(0, SIZE);

        // Evitar que o ponto seja o indice máximo do cromossomo.
        // Se o o indice for esse, não haverá cruzamento pois a primeira parte da
        // divisão do cromossomo tem tamanho igual ao tamanho dele.
        while (indexPointDivision < 1)
        {
            indexPointDivision = generateRandomInt(0, SIZE);
        }
    }

    if (enabledLogs)
        std::cout << "indexPointDivision " << indexPointDivision << std::endl;

    // Efetuar cruzamento da população
    // std::vector<Chromosome> chromosomesTEMP = chromosomes;
    //chromosomesSelected.clear();

    std::vector<Chromosome> chromosomesSelectedTEMP = chromosomesSelected;
    chromosomesSelected.clear();
    for (unsigned i = 0; i < chromosomesSelectedTEMP.size(); i+=2)
    {

        const Chromosome &parent1 = chromosomesSelectedTEMP[i];
        const Chromosome &parent2 = chromosomesSelectedTEMP[i+1];

        Chromosome child;

        for (int i = 0; i < indexPointDivision; i++)
        {
            child.setGene(parent1.getGene(i));
        }

        for (unsigned i = indexPointDivision; i < parent2.getSize(); i++)
        {
            child.setGene(parent2.getGene(i));
        }
        chromosomesSelected.push_back(child);
    }

    if (enabledLogs)
    {
        std::cout << "chromosomesSelected size [initial: " << chromosomesSelected.size() << "] - [chromosomes.size(): " << chromosomes.size() << ']' << std::endl;

        show();
    }

    std::cout << "\n\n[selec.single] Selectioned size [" << chromosomesSelected.size() << "]\n\n";
}

bool Population::getDecisionProb(unsigned percent)
{
    std::vector<bool> range(100);
    for (unsigned i = 0; i < percent; i++)
    {
        range[i] = true;
    }

    int randIndex = generateRandomInt(0, 100);
    return (range[randIndex]);
}

// Efetuar mutações na população atual
// Cada mutação será um novo indivíduo no vetor
// Estas mutações ocorrerão seguindo uma probabilidade aleatória
void Population::mutationInsertion()
{
    unsigned probability = getConfig("configurations/GA/mutation/insertion/probability")[0];

    if (enabledLogs)
        std::cout << "Ocorrency probability: " << probability << "%   \n";

    /*
        std::vector<bool> range(100);
        for (unsigned i = 0; i < probability; i++)
        {
            range[i] = true;
        }
    */
    unsigned count = 0;
    std::vector<Chromosome> chromosomesTEMP = chromosomesSelected;
    for (unsigned i = 0; i < chromosomesTEMP.size(); ++i)
    {
        // Calcular probabilidade (porcentagens inteiras ex.: 1%)

        // int randIndex = generateRandomInt(0, 100);
        bool makeMutation = !getDecisionProb(probability); // !(range[randIndex]);
        if (makeMutation)
        {
            if (enabledLogs)
                std::cout << "[" << i << "|N/M]\t";
            continue;
        }
        else
        {
            if (enabledLogs)
                std::cout << "[" << i << "|ok]\t";
        }

        unsigned chromosomeSize = chromosomesTEMP[i].getSize();

        unsigned index1 = 0, index2 = 0;
        while (index1 == index2)
        {
            index1 = generateRandomInt(0, chromosomeSize);
            index2 = generateRandomInt(0, chromosomeSize);
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

        chromosomesSelected.push_back(mutation);

        count++;
    }

    // juntar a população selecionada com a população oficial
    for(unsigned i = 0; i < chromosomesSelected.size(); i++)
    {
        chromosomes.push_back(chromosomesSelected[i]);
    }


    if (enabledLogs)
    {
        std::cout << "\nPopulation size [initial: " << chromosomesTEMP.size() << "] - [final: " << chromosomes.size() << ']' << std::endl;

        show();
    }

    std::cout << "\n\n[mut.inse] Selectioned size [" << chromosomesSelected.size() << "]\n\n";
}

void Population::mutationUniform(const float MIN_VALUE, const float MAX_VALUE)
{
    unsigned probability = getConfig("configurations/GA/mutation/uniform/probability")[0];

    if (enabledLogs)
        std::cout << "Ocorrency probability: " << probability << "%   \n";

    unsigned count = 0;
    std::vector<Chromosome> chromosomesTEMP = chromosomesSelected;
    for (unsigned i = 0; i < chromosomesTEMP.size(); ++i)
    {
        bool makeMutation = !getDecisionProb(probability);
        if (makeMutation)
        {
            if (enabledLogs)
                std::cout << "[" << i << "|N/M]\t";
            continue;
        }
        else
        {
            if (enabledLogs)
                std::cout << "[" << i << "|ok]\t";
        }

        // Gerar um valor válido e inserir em um indice aleatório

        float valueToInsert = generateRandomFloat(MIN_VALUE, MAX_VALUE); // dist3(mt);
        unsigned index = generateRandomInt(0, chromosomesTEMP[i].getAllGenes().size());

        Chromosome mutation = chromosomesTEMP[i];

        mutation.changeGene(index, valueToInsert);
        mutation.setFitness(0);
        mutation.resetFitness();
        chromosomesSelected.push_back(mutation);

        count++;
    }

    // juntar a população selecionada com a população oficial
    for(unsigned i = 0; i < chromosomesSelected.size(); i++)
    {
        chromosomes.push_back(chromosomesSelected[i]);
    }

    if (enabledLogs)
    {
        std::cout << "\ncount: " << count << std::endl;
        std::cout << "chromosomesTEMP size: " << chromosomesTEMP.size() << std::endl;
        std::cout << "chromosomesNEWSIZE: " << chromosomes.size() << std::endl;
        std::cout << std::endl;

        show();
    }

    std::cout << "\n\n[mut.unif] Selectioned size [" << chromosomesSelected.size() << "]\n\n";
}

std::vector<Chromosome> Population::getCurrentPopulation() const
{
    return chromosomes;
}

void Population::setChromossomeFitness(const unsigned index, const float fitness)
{

    // std::cout << "recorde: " << recordFitness << "  chromosomes[0].getFitness(): " << chromosomes[0].getFitness() << std::endl;

    // Guardar o recorde de fitness dos cromossomos gerados
    recordFitness = (recordFitness < fitness) ? fitness : recordFitness;

    chromosomes[index].setFitness(fitness);
}

void Population::enablePrintLogs(bool enable)
{
    enabledLogs = enable;
}

void Population::executeElitism()
{
    std::cout << "--- EXECUTANDO ELITISMO ---\n";
    // Para uma população de k indivíduos, pegar os k melhores cromossomos
    // efetuar ordenação de fitness e pegar apenas os k melhores dentre a população

    std::cout << "\nTam. Antes do elitismo: " << chromosomes.size() << std::endl;
    std::cout << "Fitness da populacao antes do elitismo:\n";
    for (unsigned int i = 0; i < chromosomes.size(); i++)
    {
        std::cout << "[" << chromosomes[i].getFitness() << "] ";
    }
    puts("\n\n");

    // misturar cromossomos
    //shuffleChromossomes(chromosomes);

    std::sort(chromosomes.begin(), chromosomes.end(),
              [](Chromosome &c1, Chromosome &c2)
              { return c1.getFitness() > c2.getFitness(); });

    // Obter quantidade de cromossomos que serão subtraidos da ponta do vertor de cromossomos

    unsigned cut = chromosomes.size() - initialPopulationSize;

    for (unsigned i = 0; i < cut; i++)
    {
        chromosomes.pop_back();
    }

    std::cout << "\nTam. Pos elitismo: " << chromosomes.size() << std::endl;
    std::cout << "Melhores fitness: ";
    for (unsigned int i = 0; i < chromosomes.size(); i++)
    {
        std::cout << "[" << chromosomes[i].getFitness() << "] ";
    }
    puts("\n");
}
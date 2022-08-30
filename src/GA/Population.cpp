#include "GA/Population.h"

Population::Population() 
{ 
    loadConfiguration(); 
}

Population::~Population() { }

float getRandomFloat()
{
    return static_cast<float>((rand()%10000)) / 1000;
}

void Population::createInitialPopulation(const unsigned POPULATION_SIZE, const unsigned CHROMOSSOME_SIZE)
{
    for (size_t i = 0; i < POPULATION_SIZE; i++)
    {
        Chromosome c;
        for (size_t j = 0; j < CHROMOSSOME_SIZE; j++)
        {
            float randFloat = getRandomFloat();
            c.setGene(randFloat);
        }
        c.setRandomFitness();
        chromosomes.push_back(c);
    }   
}

void Population::show()
{
    for(auto& c : chromosomes) { c.show(); }
}

void Population::generateNewPopulation(NewGenParams newGenParams)
{
    /// seleção ///
    switch (newGenParams.selectionType)
    {
    case SELECTION_TYPE::FITNESS:
        std::cout << "Seleção FITNESS" << std::endl;
        break;
    case SELECTION_TYPE::TOURNAMENT:
        std::cout << "Seleção TOURNAMENT" << std::endl;
        break;
    case SELECTION_TYPE::ROULLETE:
        std::cout << "Seleção ROULLETE" << std::endl;
        break;
    case SELECTION_TYPE::ESTOCASTIC:
        std::cout << "Seleção ESTOCASTIC" << std::endl;
        selectionEstocastic();
        break;
    default:
        break;
    }

    /// cruzamento ///
    switch (newGenParams.crossoverType)
    {
    case CROSSOVER_TYPE::SINGLE_POINT:
        std::cout << "crossover SINGLE_POINT" << std::endl;
        break;
    case CROSSOVER_TYPE::MULTI_POINT:
        std::cout << "crossover MULTI_POINT" << std::endl;
        break;
    case CROSSOVER_TYPE::UNIFORM:
        std::cout << "crossover UNIFORM" << std::endl;
        crossoverUniform();
        break;
    default:
        break;
    }

    /// cruzamento ///
    switch (newGenParams.mutationType)
    {
    case MUTATION_TYPE::INSERTION:
        std::cout << "mutation INSERTION" << std::endl;
        break;
    case MUTATION_TYPE::INVERSION:
        std::cout << "mutation INSERTION" << std::endl;
        break;
    case MUTATION_TYPE::UNIFORM:
        std::cout << "mutation UNIFORM" << std::endl;
        break;
    default:
        break;
    }
}


// fitness: vetor com todos os fitness que estarao na roleta
// qtdNidles: quantidade de agulhas na roleta
// spin: giro da roleta; porcentagem do giro 1% - 99%
void Population::selectionEstocastic()
{
    const unsigned qtdNidles = configuration.selection.estocastic.second;
    srand(time(NULL));
    const unsigned spin = (rand() % 99);

    float fitnessSum = 0;
    for (Chromosome &c : chromosomes) {  fitnessSum += c.getFitness(); }
    
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

    std::deque<unsigned> roulette {};
    for(unsigned int i = 0; i < percents.size(); i++)
    {
        for (unsigned j = 0; j < percents[i]; j++)
        {
            roulette.push_back(i);
        }  
    }

    /// girar a roleta

    for (unsigned i = 0; i < spin; i++) { roulette.push_back(roulette[i]); }
    for (unsigned i = 0; i < spin; i++) { roulette.pop_front(); }
  
    // Calcular indices das agulhas em relação a roleta

    std::vector<unsigned> indexNidles {};
    for (size_t i = 0; i < qtdNidles; i++)
    {
        unsigned index = ((100 / qtdNidles) * i) + ((100 / qtdNidles)/2);
        indexNidles.push_back(index);
    }

    // Efetuar seleção dos indices dos cromossomos que as agulhas apontam

    std::set<unsigned> selectionIndexes {};
    for (unsigned& i : indexNidles)
    {
        selectionIndexes.insert(roulette[i]);
    }

    std::vector<Chromosome> chromosomesTEMP = chromosomes;
    chromosomes.clear();

    for (const unsigned& i : selectionIndexes)
    {
        chromosomes.push_back(chromosomesTEMP[i]);
    }

}


// No cruzamento, serão selecionados pares de cromossomos:
// Por exemplo, em um vetor de 4 cromossomos, o cruzamento será de
// (0,1) e (2,3). Em caso de impares, o ultimo cruzará com um cromossomo aleatório do votor.
void Population::crossoverUniform()
//(const std::vector<float>& parent1, const std::vector<float>& parent2, const unsigned& taxParent1, const unsigned& taxParent2)
{
    std::cout << "================" << "crossoverUniform()" << "================" << std::endl;
    const unsigned taxParent1 = configuration.crossover.uniform.second[0];
    const unsigned taxParent2 = configuration.crossover.uniform.second[1];

    exit(0);
    // verificar se o vetor de cromossomos tem mais de 1 cromossomo
    if(chromosomes.size() < 2) return;

    // verificar se o vetor de cromossomos tem uma quantidade impar
    if(chromosomes.size()%2==1)
    {
        // se tiver, selecionar um cromossomo aleatorio e inserir no final
        srand(time(NULL));
        unsigned index = (rand()%chromosomes.size());
        chromosomes.push_back(chromosomes[index]);
    }

    std::vector<float> children {};

    for (size_t i = 0; i < chromosomes.size(); i++)
    {
        const std::vector<float>& parent1 = chromosomes[i  ].getAllGenes();
        const std::vector<float>& parent2 = chromosomes[i+1].getAllGenes();

        if(parent1.size() != parent1.size())
        {
            std::cerr << "Error: parent1 and parent2 must have the same size." << std::endl;
        }

        if(taxParent1 + taxParent2 != 100)
        {
            std::cerr << "Error: Invalid number of taxParent1." << std::endl;
        }


        size_t chromossomeSize = (parent1.size() + parent2.size()) / 2;
        unsigned parent1size = (chromossomeSize * taxParent1) / 100;
        unsigned parent2size = chromossomeSize - parent1size;

        // Produzir a mascara binária;
        // Será gerado trues de acordo com a porcentagem do pai 1;
        // Será gerado falses com a quantidade que faltar para completar a mascara;

        std::vector<bool> mask {};
        for (size_t i = 0; i < parent1size; i++) { mask.push_back(true); }
        for (size_t i = 0; i < parent2size; i++) { mask.push_back(false); }

        // Embaralhar mascara de forma aleatória
        
        std::random_device randDevice {};
        std::default_random_engine randEngine{randDevice()};
        std::shuffle(std::begin(mask), std::end(mask), randEngine);

        // Efetuar cruzamento a partir da mascara

        for (size_t i = 0; i < mask.size(); i++)
        {
            if(mask[i] == true) {
                children.push_back(parent1[i]);
            } 
            else {  
                children.push_back(parent2[i]);
            }
        }
    }
    
    _debug("CHILDREN ", children);

}


std::vector<float> Population::mutationInsertion(const std::vector<float>& chromosome)
{
    size_t chromosomeSize = chromosome.size();

    srand((unsigned int)time(NULL));
    unsigned index1 = 0, index2 = 0;
    while (index1 == index2) 
    {
        index1 = (rand() % chromosomeSize*100)/100;
        index2 = (rand() % chromosomeSize*100)/100;
    }
    
    // Ordenar indices - index1 deve conter menor valor dos dois

    if(index1 > index2)
    {
        unsigned temp = index1;
        index1 = index2;
        index2 = temp;
    }
    
    std::vector<float> mutation {};

    // Salvar valor de (index1) para variavel (auxiliar)
    // Copiar para mutation os valores até (index2)-1, pulando o valor de (index1)
    // Inserir valor de (auxiliar) em (index2)-1
    // Copiar para mutation os valores restantes a partir de (index2)

    float aux = chromosome[index1];
    for (size_t i = 0; i < index2; i++)
    {
        if(i == index1){ continue; }
        mutation.push_back(chromosome[i]);
    }

    mutation.push_back(aux);

    for (size_t i = index2; i < chromosomeSize; i++)
    {
        mutation.push_back(chromosome[i]);
    }

    return mutation; 

}


std::vector<Chromosome> Population::getCurrentPopulation()
{
    return chromosomes;
}


void Population::loadConfiguration()
{
    std::ifstream file("GAConfiguration.ini");
    Configuration configuration;
    std::string key, value;

    // selection/fitness
    file >> key; file >> key; 
    file >> key >> value;
    configuration.selection.fitness = std::make_pair(key, value);

    // selection/tournament
    file >> key; 
    file >> key >> value;
    configuration.selection.tournament = std::make_pair(key, value);
    
    // selection/roullete
    file >> key; 
    file >> key >> value;
    configuration.selection.roullete = std::make_pair(key, (unsigned)std::stoi(value));

    // selection/estocastic
    file >> key; 
    file >> key >> value;
    configuration.selection.estocastic = std::make_pair(key, (unsigned)std::stoi(value));
    
    // crossover/singlepoint
    file >> key; file >> key; 
    file >> key >> value;
    configuration.crossover.singlepoint = std::make_pair(key, (unsigned)std::stoi(value));

    // crossover/multipoint
    file >> key; 
    file >> key >> value;
    std::vector<unsigned> value_vector1;
    for(auto& i : value)
    {
        if(i != '-') { value_vector1.push_back(atoi(&i)); }
    }
    configuration.crossover.multipoint = std::make_pair(key, value_vector1);
    _debug("crossover/multipoint", value_vector1, " ");
    // crossover/uniform
    file >> key; 
    file >> key >> value;

    if(value.size() != 5){ std::cerr << "crossover/uniform: [Erro] Parametro deve seguir o padão: 00-00\n"; exit(-1); }
    std::vector<unsigned> value_vector2;

    unsigned val1 = (static_cast<unsigned>(value[0]) - 48) * pow(10, 1) + 
                    (static_cast<unsigned>(value[1]) - 48) * pow(10, 0);

    unsigned val2 = (static_cast<unsigned>(value[3]) - 48) * pow(10, 1) + 
                    (static_cast<unsigned>(value[4]) - 48) * pow(10, 0);
    
    
    value_vector2.push_back(val1);
    value_vector2.push_back(val2);

    configuration.crossover.uniform = std::make_pair(key, value_vector2);
    _debug("crossover/uniform", value_vector2, " "); exit(0);
    // mutation/insertion
    file >> key; file >> key; 
    file >> key >> value;
    configuration.mutation.insertion = std::make_pair(key, value);

    // mutation/inversion
    file >> key; 
    file >> key >> value;
    configuration.mutation.inversion = std::make_pair(key, value);
    
    // mutation/uniform
    file >> key; 
    file >> key >> value;
    configuration.mutation.uniform = std::make_pair(key, value);
    
}
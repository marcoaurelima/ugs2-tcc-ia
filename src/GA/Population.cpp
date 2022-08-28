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
std::set<float> Population::selectionEstocastic(const std::vector<float>& fitness, const unsigned& qtdNidles, const unsigned& spin)
{
    float fitnessSum = 0;
    for (auto &i : fitness) {  fitnessSum += i; }
    
    // Produzir um vetor de aprox. de 100 posições (valores float as vezes somam 99% no total),
    // onde terão vários blocos de valores repetidos representando as fatias da roleta.
    // cada bloco conterá o indice do cromossomo. Ex.: 001111222
    // No caso acima, o fitness na posição 2 tem uma fatia maior, enquanto o 0 tem a menor.

    std::vector<unsigned> percents;
    for (unsigned i = 0; i < fitness.size(); i++)
    {
        unsigned value = (fitness[i] / fitnessSum) * 100;
        percents.push_back(value);
    }
    
    // Preencher a roleta com blocos de valores

    std::deque<float> roleta {};
    for(unsigned int i = 0; i < percents.size(); i++)
    {
        for (unsigned j = 0; j < percents[i]; j++)
        {
            roleta.push_back(i);
        }  
    }

    /// girar a roleta

    for (unsigned i = 0; i < spin; i++) { roleta.push_back(roleta[i]); }
    for (unsigned i = 0; i < spin; i++) { roleta.pop_front(); }
  
    // Calcular indices das agulhas

    std::vector<unsigned> indexNidles {};
    for (size_t i = 0; i < qtdNidles; i++)
    {
        int index = ((100 / qtdNidles) * i) + ((100 / qtdNidles)/2);
        indexNidles.push_back(index);
    }

    // Efetuar seleção com base no indice das agulhas

    std::set<float> selection {};
    for (unsigned& i : indexNidles)
    {
        selection.insert(roleta[i]);
    }

    return selection;

}


// parent1 / parent2:       Cromossomos dos pais
// taxParent1 / taxParent2: taxa em porcentagem da participação dos respectivos pais no cruzamento. 
std::vector<float> Population::crossoverUniform(const std::vector<float>& parent1, const std::vector<float>& parent2, const unsigned& taxParent1, const unsigned& taxParent2)
{
    if(parent1.size() != parent2.size())
    {
        std::cerr << "Error: parent1 and parent2 must have the same size." << std::endl;
        return std::vector<float>();
    }

    if(taxParent1 + taxParent2 != 100)
    {
        std::cerr << "Error: Invalid number of taxParent1." << std::endl;
        return std::vector<float>();
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

    std::vector<float> child {};
    for (size_t i = 0; i < mask.size(); i++)
    {
        if(mask[i] == true) {
            child.push_back(parent1[i]);
        } 
        else {  
            child.push_back(parent2[i]);
        }
    }

    return child;
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
    std::vector<unsigned> value_vector;
    for(auto& i : value)
    {
        if(i != '-') { value_vector.push_back(atoi(&i)); }
    }
    configuration.crossover.multipoint = std::make_pair(key, value_vector);
    
    // crossover/uniform
    file >> key; 
    file >> key >> value;
    configuration.crossover.uniform = std::make_pair(key, value);

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
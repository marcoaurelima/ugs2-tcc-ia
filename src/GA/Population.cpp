#include "GA/Population.h"

Population::Population() { }

Population::~Population() { }

float getRandomFloat()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 10.0);

    return dist(mt);
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
    std::cout << "------------------------------- Population: ------------------------------- " << std::endl;
    for(auto& c : chromosomes) { c.show(); }
    std::cout << "---------------------------------------------------------------------------\n\n" << std::endl;
}


void Population::generateNewPopulation(NewGenParams newGenParams)
{
    /// seleção ///
    switch (newGenParams.selectionType)
    {
    case SELECTION_TYPE::FITNESS:
        std::cout << "ETAPA: Seleção    MÉTODO: Fitness" << std::endl;
        break;
    case SELECTION_TYPE::TOURNAMENT:
        std::cout << "ETAPA: Seleção    MÉTODO: Tournament" << std::endl;
        break;
    case SELECTION_TYPE::ROULLETE:
        std::cout << "Seleção ROULLETE" << std::endl;
        break;
    case SELECTION_TYPE::STOCHASTIC_US:
        std::cout << "ETAPA: Seleção    MÉTODO: Stochastic Universal Sampling" << std::endl;
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
        std::cout << "ETAPA: Mutação    MÉTODO: Inserção" << std::endl;
        mutationInsertion();
        break;
    case MUTATION_TYPE::INVERSION:
        std::cout << "ETAPA: Mutação    MÉTODO: Inverção" << std::endl;
        break;
    case MUTATION_TYPE::UNIFORM:
        std::cout << "ETAPA: Mutação    MÉTODO: Uniform" << std::endl;
        break;
    default:
        break;
    }
}


std::vector<unsigned> Population::getConfig(const std::string& path)
{
    std::ifstream stream(path);
    if(!stream.is_open()){ std::cout << "ERROR: configuration \"" << path << "\" not found." << std::endl; }
    std::vector<unsigned> values;
    std::string v;
    while(stream >> v)
    {
        values.push_back(std::stoi(v));
    }

    return values;
}


// fitness: vetor com todos os fitness que estarao na roleta
// qtdNidles: quantidade de agulhas na roleta
// spin: giro da roleta; porcentagem do giro 1% - 99%
void Population::selectionEstocastic()
{   
    const unsigned qtdNidles = getConfig("configurations/GA/selection/estocastic/qtdneedles")[0];

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 99);

    const unsigned spin = dist(mt);

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
    
    std::cout << "qtdNidles " << qtdNidles << "    ";
    std::cout << "indexNidles ";
    for(auto& i : indexNidles){ std::cout << i << " "; }
    std::cout  << "   ";
    std::cout << "spin " << spin << std::endl;
    std::cout << "selectionIndexes ";
    for(auto& i : selectionIndexes){ std::cout << i << " "; }
    std::cout  << "    \n";
    show();

}


// No cruzamento, serão selecionados pares de cromossomos:
// Por exemplo, em um vetor de 4 cromossomos, o cruzamento será de
// (0,1) e (2,3). Em caso de impares, o ultimo cruzará com um cromossomo aleatório do votor.
void Population::crossoverUniform()
{
    const unsigned taxParent1 = getConfig("configurations/GA/crossover/uniform/contrib")[0];
    const unsigned taxParent2 = getConfig("configurations/GA/crossover/uniform/contrib")[1];
    std::cout << "taxParent1 " << taxParent1 << "%    " << "taxParent2 " << taxParent2 << "%" << std::endl;
    std::cout << "masks ";

    // verificar se o vetor de cromossomos tem mais de 1 cromossomo
    if(chromosomes.size() < 2) return;

    // verificar se o vetor de cromossomos tem uma quantidade impar
    if(chromosomes.size()%2==1)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, chromosomes.size()-1);

        // se tiver, selecionar um cromossomo aleatorio e inserir no final

        unsigned index = dist(mt);
        chromosomes.push_back(chromosomes[index]);
    }

    std::vector<Chromosome> chromosomeTEMP = chromosomes;
    chromosomes.clear();

    for (size_t i = 0; i < chromosomeTEMP.size(); i+=2)
    {
        Chromosome parent1 = chromosomeTEMP[i  ];
        Chromosome parent2 = chromosomeTEMP[i+1];
        Chromosome child {};

        if(parent1.getAllGenes().size() != parent1.getAllGenes().size())
        {
            std::cerr << "Error: parent1 and parent2 must have the same size." << std::endl;
        }

        if(taxParent1 + taxParent2 != 100)
        {
            std::cerr << "Error: Invalid number of taxParent1." << std::endl;
        }

        size_t chromossomeSize = (parent1.getAllGenes().size() + parent2.getAllGenes().size()) / 2;
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
            if(mask[i] == false) {
                child.setGene(parent1.getGene(i));
            } 
            else {  
                child.setGene(parent2.getGene(i));
            }
        }

        chromosomes.push_back(child);

        for(auto i : mask){ std::cout << i; } std::cout << "    ";
    }

    std::cout << std::endl;
    
    show();
 
}


// Efetuar mutações na população atual
// Cada mutação será um novo indivíduo no vetor
// Estas mutações ocorrerão seguindo uma probabilidade aleatória
void Population::mutationInsertion()
{
    unsigned probability = getConfig("configurations/GA/mutation/insertion/probability")[0];
    std::cout << "Ocorrency probability: " << probability << "%   \n";

    unsigned count = 0;
    for(Chromosome& c : chromosomes) 
    {
        // Calcular probabilidade (porcentagens inteiras ex.: 1%)
        std::vector<bool> range(100);
        
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> dist(0, 100);
        
        for(unsigned i = 0; i < probability; i++) range[dist(mt)] = true;

        bool makeMutation = range[dist(mt)];
        if(!makeMutation){ std::cout << "indexes-mutation(" << count << ") No-Mutation.   "; continue; }

        unsigned chromosomeSize = c.getSize();

        std::uniform_int_distribution<unsigned> dist2(0,chromosomeSize-1);
        unsigned index1 = 0, index2 = 0;
        while (index1 == index2) 
        {
            index1 = dist2(mt);
            index2 = dist2(mt);
        }
        
        // Ordenar indices - index1 deve conter menor valor dos dois

        if(index1 > index2)
        {
            unsigned temp = index1;
            index1 = index2;
            index2 = temp;
        }
        
        std::cout << "indexes-mutation(" << count << "): [" << index1 << "]["<< index2 << "]   ";
        Chromosome mutation {};

        // Salvar valor de (index1) para variavel (auxiliar)
        // Copiar para mutation os valores até (index2)-1, pulando o valor de (index1)
        // Inserir valor de (auxiliar) em (index2)-1
        // Copiar para mutation os valores restantes a partir de (index2)

        float aux = c.getGene(index1);
        for (size_t i = 0; i < index2; i++)
        {
            if(i == index1){ continue; }
            mutation.setGene(c.getGene(i));
        }

        mutation.setGene(aux);

        for (size_t i = index2; i < chromosomeSize; i++)
        {
            mutation.setGene(c.getGene(i));
        }

        chromosomes.push_back(mutation);

        count++;
    }

    std::cout << std::endl;
    
    show();

}


std::vector<Chromosome> Population::getCurrentPopulation()
{
    return chromosomes;
}



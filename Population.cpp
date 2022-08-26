#include "Population.h"

Population::Population() { }

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
std::set<float> Population::selectionEstocastic(std::vector<float> fitness, unsigned qtdNidles, unsigned spin)
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
    
    #ifdef DEBUG
    for (auto &i : roleta) { std::cout << i; }
    puts("");
    #endif

    /// girar a roleta

    for (unsigned i = 0; i < spin; i++) { roleta.push_back(roleta[i]); }
    for (unsigned i = 0; i < spin; i++) { roleta.pop_front(); }
    
    #ifdef DEBUG
    for (auto &i : roleta) { std::cout << i; }
    puts("");
    #endif

    // Calcular indices das agulhas

    std::vector<unsigned> indexNidles {};
    for (size_t i = 0; i < qtdNidles; i++)
    {
        int index = ((100 / qtdNidles) * i) + ((100 / qtdNidles)/2);
        indexNidles.push_back(index);
    }

    #ifdef DEBUG
    for (auto &i : indexNidles) { std::cout << i << " "; }
    puts("");
    #endif

    // Efetuar seleção com base no indice das agulhas

    std::set<float> selection {};
    for (unsigned& i : indexNidles)
    {
        selection.insert(roleta[i]);
    }

    #ifdef DEBUG
    std::cout << "Selection: " << std::endl;
    for (auto &i : selection) { std::cout << i << " "; }
    puts("");
    #endif

    return selection;

}
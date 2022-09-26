#include <iostream>
#include <fstream>
#include <array>
#include <deque>
#include <set>
#include <random>
#include <algorithm>
#include <initializer_list>
#include "GA/Population.h"
#include "GA/types.h"

#include "NN/types.h"
#include "NN/NeuralNetwork.h"

#include "NeuroEvolutiveEngine.h"

using std::cout;
int main()
{

    // população inicial
    Population population;
    population.createInitialPopulation(5, 27);
    population.setNewGenerationParams(NewGenParams{
        SELECTION_TYPE::ROULLETE,
        CROSSOVER_TYPE::SINGLE_POINT,
        MUTATION_TYPE::INSERTION});
    //population.enablePrintLogs(false);

    // definição da topologia da rede neural
    NeuralNetwork network;
    network.setInputLayer(InputLayerInfo(2));
    network.setHiddenLayer(HiddenLayerInfo({3, 3}, ACTFUNC::SIGMOID));
    network.setOutputLayer(OutputLayerInfo(1, ACTFUNC::SIGMOID));

    // Dados do jogo em tempo real
    float pontuation = 20.0, distance = 5.0, value = 0.0;

    NeuroEvolutiveEngine engine(population, network);
    engine.showInternalStatus();


    auto r = engine.takeDecision({pontuation, distance});

exit(0);
    for (int i = 0; i < 20; i++)
    {
        value += 0.01;
        auto r = engine.takeDecision({pontuation, distance});
        cout << "Decision1: " << r[0] << endl;
        engine.setCurrentChromossomeFitness(value);
        //engine.showInternalStatus();

        engine.useNextTopology();
    }

    /*
    * o algoritmo foi testado e está funcionando sem erros
    * obs. depois que é criado uma nova geração de cromossomos
    * a população obviamente fica maior. Então o chromossomo current
    * volta ao indice 0, e então é reiniciado os testes de topologia
    * a fim de definir o fitness de todos. 
    * no caso do laço 'for' acima, depois dessa de gerado essa nova população,
    * começa-se a preencher os cromossomos com seu respsctivo fitness a partir
    * do indice 0, mas o valor usado será o da variável 'value', que é um
    * acumulador de valores. Não se deve estranhar se a segunda geração de
    * cromossomos possuir fitness com valores grandes no começo, pois
    * o valor de 'value' continua a partir de onde parou na geração passada.
    */



    return 0;
}
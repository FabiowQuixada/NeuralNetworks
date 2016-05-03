#include "neural_network.h"

#include "halfedge.h"

#include <cmath>

void wait();

bool NeuralNetwork::printing = false;
int  NeuralNetwork::neuralNetworkID = 0;

NeuralNetwork::NeuralNetwork()
{
    ID = neuralNetworkID++;
    _threshold = 0.0;
    _allocated_layers = 0;
    _length = 0;
    layers = NULL;
}

NeuralNetwork::~NeuralNetwork() {}

int    NeuralNetwork::id() const {return ID;}
Layer* NeuralNetwork::inputLayer() const {return layers[0];}
Layer* NeuralNetwork::outputLayer() const {return layers[_length-1];}

void NeuralNetwork::load(const char *fileName)
{
    std::ifstream file;
    file.open(fileName);
    int l;
    int neurons;

    if(file.is_open())
    {
        file >> l; //  Number of layers;

        layers = new Layer*[l];
        _length = l;

        for(int i = 0; i < l; ++i)
        {
            file >> neurons; // Number of neurons in the l-th layer;

            add_layer(new Layer(neurons));
        }

        /// TODO: Options;
    }

    for(int i = 0; i < _length-1; ++i)
        layer(i)->connectTo(layer(i+1));

    file.close();
}

void NeuralNetwork::add_layer(Layer *l)
{
    if(_allocated_layers > _length)
    {
        std::cout << "passou!";
        return;
    }

    if(_length == 0)
    {
        std::cout << "NeuralNetwork: Erro - vetor de Layers nao alocado.";
        return;
    }

    l->set_network(this);
    layers[_allocated_layers++] = l;
}

int NeuralNetwork::length() const {return _length;}

void NeuralNetwork::set_length(int n)
{
    layers = new Layer*[n];
    _length = n;
}

Layer* NeuralNetwork::layer(int i) const
{
    if(i >= 0 and i <= _length)
        return layers[i];

    std::cout << "NeuralNetwork: Erro - Indice fora da lista de camadas.";
    std::cout << " - Numero de camadas: " << _length << std::endl;
    std::cout << " - Indice: " << i << std::endl;
    wait();

    return inputLayer();
}

int* NeuralNetwork::test(Pattern p) const
{
    // An array of results, one for each output neuron;
    int *resultList = new int[outputLayer()->length()];

    // For each neuron 'b' in the output layer...
    for(int b = 0; b < outputLayer()->length(); ++b)
    {
        float result = outputLayer()->neuron(b)->bias();

        // For each neuron 'a' in the input layer...
        for(int a = 0; a < inputLayer()->length(); ++a) // result = the weight between neurons 'a' and 'b' times the correspoding pattern unit;
            result += inputLayer()->neuron(a)->edgeTo(outputLayer()->neuron(b))->weight() * p.input(a);

        resultList[b] = result;
    }

    for(int b = 0; b < outputLayer()->length(); ++b)
        std::cout << resultList[b] << " :: " << (resultList[b] > 0 ? "Sim!" : "Não!") << std::endl;

    return resultList;
}

void NeuralNetwork::set_input(Pattern p)
{
    for(int a = 0; a < inputLayer()->length(); ++a)
        inputLayer()->neuron(a)->set_activation(p.input(a));
}

bool NeuralNetwork::inputOK(Pattern p) const
{
    if(p.size() == inputLayer()->length()) return true;

    std::cout << "NeuralNetwork: Erro - Tamanho de padrao inconsistente." << std::endl;
    std::cout << " - Tamanho do padrao: " << p.size() << std::endl;
    std::cout << " - Tamanho da camada de entrada: " << inputLayer()->length() << std::endl;
    wait();

    return false;
}

bool NeuralNetwork::inputOK(PatternList patternList) const
{
    PatternList::iterator pattern_it;

    for(pattern_it = patternList.begin(); pattern_it != patternList.end(); ++pattern_it)
        if((*pattern_it)->size() != inputLayer()->length())
        {
            std::cout << "NeuralNetwork: Erro - Tamanho de padrao inconsistente." << std::endl
                      << " - Tamanho do padrao: " << (*pattern_it)->size() << std::endl
                      << " - Tamanho da camada de entrada: " << inputLayer()->length() << std::endl;
            wait();
            return false;
        }

    return true;
}

bool NeuralNetwork::outputOK(int output) const
{
    if(outputLayer()->length() == 1) return true;

    std::cout << "NeuralNetwork: Erro - Tamanho da saida inconsistente." << std::endl;
    std::cout << " - Tamanho da saida: 1" << std::endl;
    std::cout << " - Tamanho da camada de saida: " << outputLayer()->length() << std::endl;
    wait();

    return false;
}

bool NeuralNetwork::outputOK(IntList targetList) const
{
    if(targetList.size() == (unsigned int) outputLayer()->length()) return true;

    std::cout << "NeuralNetwork: Erro - Tamanho da saida inconsistente." << std::endl;
    std::cout << " - Tamanho da saida: " << targetList.size() << std::endl;
    std::cout << " - Tamanho da camada de saida: " << outputLayer()->length() << std::endl;
    wait();

    return false;
}

bool NeuralNetwork::consistentTrainningPair(PatternList patternList, IntList targetList) const
{
    if(patternList.size() == targetList.size()) return true;

    std::cout << "NeuralNetwork: Erro - Tamanhos do par de treinamento inconsistentes." << std::endl;
    std::cout << " - Numero de padroes: " << patternList.size() << std::endl;
    std::cout << " - Numero de saidas: " << targetList.size() << std::endl;
    wait();

    return false;
}

void NeuralNetwork::print()
{
    std::cout << "K: " << _allocated_layers << std::endl
              << "Numero de camadas: " << length() << std::endl;
}

std::ostream &operator<<(std::ostream &output, const NeuralNetwork net)
{
	int i = 0;

	std::cout << std::endl;
	std::cout << "Rede Neural " << net.id() << std::endl;

	std::cout << "  Lista de neurons:" << std::endl;

    for(int l = 0; l < net.length(); ++l)
    {
        if(net.length()==1)
            std::cout << "   ~~ Camada Unica ~~~~~~~~~~~~~~~~" << std::endl;
        else
            if(i==net.length()-1)  std::cout << "   ~~ Camada " << i++ << " (SAIDA) ~~~~~~~~~~~~~~~~" << std::endl;
            else if(i==0)               std::cout << "   ~~ Camada " << i++ << " (ENTRADA) ~~~~~~~~~~~~~" << std::endl;
            else                        std::cout << "   ~~ Camada " << i++ << " ~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

        for(int a = 0; a < net.layer(l)->length(); ++a)
            std::cout << "     " << *net.layer(l)->neuron(a) << std::endl;
    }

	return output;
}


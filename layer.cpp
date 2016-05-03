#include "layer.h"

#include "neural_network.h"


//Layer::~Layer(){}

Layer::Layer(int n)
{
    net = NULL;
    _length = n;

    neuronList = new Neuron*[n];

    _position = 0;

    for(int i = 0; i < n; ++i)
        neuronList[i] = new Neuron(this);
}

int      Layer::length() const {return _length;}
Neuron*  Layer::neuron(int i) const
{
    if(i < 0 or i >= _length)
    {
        std::cout << "Layer: Erro - Indice fora da lista." << std::endl
                  << " - Numero de unidades: " << _length << " (de 0 a " << _length-1 << ")" << std::endl
                  << " - Indice: " << i << std::endl;
        wait();

        return neuronList[0];
    }

    return neuronList[i];
}

void Layer::set_network(NeuralNetwork *n) {net = n;}

void Layer::connectTo(Layer *l)
{
    for(int b = 0; b < l->length(); ++b)
       l->neuron(b)->inputMalloc(length());

    for(int a = 0; a < _length; ++a)
    {
        neuron(a)->outputMalloc(l->length());

        for(int b = 0; b < l->length(); ++b)
            Neural_HalfEdge *h = new Neural_HalfEdge(neuron(a), l->neuron(b));
    }


}

int Layer::pos() const {return -2;}

std::ostream &operator<<(std::ostream &output, const Layer l)
{
	for(int a = 0; a < l._length; ++a)
	    std::cout << *l.neuronList[a] << std::endl;

	return output;
}


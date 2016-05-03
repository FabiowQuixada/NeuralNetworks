#include "neuron.h"

#include "layer.h"
#include "halfedge.h"

int Neuron::neuronID = 0;

Neuron::Neuron(Layer *l)
{
    setup();

    layer = l;
}

Neuron::Neuron()
{
    setup();
}

void Neuron::setup()
{
    ID = neuronID++;
    _is_output = false;
    _bias = 0.0;
    _activation = 0;
    _input = 0.0;
    _output = 0.0;
    _inHalfedges = 0;
    _outHalfedges = 0;
    _allocated_inEdges = 0;
    _allocated_outEdges = 0;
    _incomingEdges = NULL;
    _outgoingEdge = NULL;
    layer = NULL;
}

Neuron::~Neuron() {}

void Neuron::connectTo(Neuron *n)
{
    if(_allocated_outEdges >= _outHalfedges)
    {
        std::cout << "Neuron: Erro - Alem dos limites da memoria (semi-arestas de saida)." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        wait();
    }

    Neural_HalfEdge *h = new Neural_HalfEdge(this, n);
}

void Neuron::send_signalIfExcited() const
{
    if(_input >= _activation) // If this neuron has been sufficiently excited...
        for(int i = 0; i < _outHalfedges; ++i) // it sends a signal for each of its successors...
            _outgoingEdge[i]->head()->addTo_input( this->_output * _outgoingEdge[i]->weight() );
}

int   Neuron::id() const {return ID;}
bool  Neuron::is_output() const {return _is_output;}
float Neuron::bias() const {return _bias;}
float Neuron::input() const {return _input;}
float Neuron::output() const {return _output;}

void Neuron::set_activation(float a) {_activation = a;}
void Neuron::addTo_activation(float a) {_activation += a;}
void Neuron::set_bias(float b) {_bias = b;}
void Neuron::addTo_bias(float b) {_bias += b;}
void Neuron::addTo_input(float i) {_input += i;}

void Neuron::add_incomingEdge(Neural_HalfEdge* h)
{
    if(_incomingEdges == NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de entrada nao-alocada:" << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << " - Defina atraves de Neuron::inputMalloc();" << std::endl;
        wait();
    } else if(_allocated_inEdges >= _inHalfedges)
    {
        std::cout << "Neuron: Erro - Memoria lotada para semi-arestas de entrada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << " - Arestas alocadas: " << _inHalfedges << ";" << std::endl;
        wait();
    }

    _incomingEdges[_allocated_inEdges++] = h;
}

void Neuron::add_outgoingEdge(Neural_HalfEdge* h)
{
    if(_outgoingEdge == NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de saida nao-alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << "Defina atraves de Neuron::outputMalloc()" << std::endl;
        wait();
    } else if(_allocated_outEdges >= _outHalfedges)
    {
        std::cout << "Neuron: Erro - Memoria lotada para semi-arestas de saida." << _allocated_outEdges << ", " << _outHalfedges << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        wait();
    }

    _outgoingEdge[_allocated_outEdges++] = h;
}

float Neuron::activation() const {return _activation;}

Neural_HalfEdge* Neuron::edgeTo(Neuron *n)
{
    if(_outgoingEdge == NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de saida nao-alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << "Defina atraves de Neuron::outputMalloc()" << std::endl;
        wait();
    }



    for(int i = 0; i < _outHalfedges; ++i)
        if(_outgoingEdge[i]->head()==n)
            return _outgoingEdge[i];

    std::cout << "Neuron: Erro - Nao ha aresta do neuron " << this->id() << " para o " << n->id() << std::endl;
    std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
    wait();

    return NULL;
}

Neural_HalfEdge* Neuron::edgeFrom(Neuron *n) const
{
    if(_incomingEdges == NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de entrada nao-alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << "Defina atraves de Neuron::inputMalloc()" << std::endl;
        wait();
    }


    for(int i = 0; i < _inHalfedges; ++i)
        if(_incomingEdges[i]->tail()==n)
            return _incomingEdges[i];

    std::cout << "Neuron: Erro - Nao ha aresta do neuron " << this->id() << " para o " << n->id() << std::endl;
    std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
    wait();

    return NULL;
}

Vector Neuron::weightVector() const
{
    Vector v(_allocated_inEdges);

    for(int i = 0; i < _allocated_inEdges; ++i)
        v.set_value(i, incomingEdge(i)->weight());

    return v;
}

Neural_HalfEdge* Neuron::edge(int i)
{
//    if(i >= 0 and i <= outgoingEdges.size())
//    {
//        HalfEdgeList::const_iterator it = outgoingEdges.begin();
//        for(int a = 0; a < i; ++a) it++;
//            return *it;
//    }

//    std::cout << "HalfEdge: Erro - Indice fora da lista.";
//    std::cout << " - Numero de unidades: " << outgoingEdges.size() << std::endl;
//    std::cout << " - Indice: " << i << std::endl;
//    std::cout << std::endl << std::endl;

    return NULL;
}

Neural_HalfEdge* Neuron::incomingEdge(int i) const
{
    if(_incomingEdges == NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de entrada nao-alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << "Defina atraves de Neuron::inputMalloc()" << std::endl;
        wait();
    } else if(i < 0 or i >= _allocated_inEdges)
    {
        std::cout << "Neuron: Erro - Indice fora da lista." << std::endl
                  << " - Numero de unidades: " << _allocated_inEdges << " (de 0 a " << _allocated_inEdges-1 << ")" << std::endl
                  << " - Indice: " << i << std::endl;
        wait();

        return NULL;
    }

    return _incomingEdges[i];
}

Neural_HalfEdge* Neuron::outgoingEdge(int i) const
{
    if(_outgoingEdge == NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de saida nao-alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        std::cout << "Defina atraves de Neuron::outputMalloc()" << std::endl;
        wait();
    } else if(i < 0 or i >= _allocated_outEdges)
    {
        std::cout << "Neuron: Erro - Indice fora da lista." << std::endl
                  << " - Numero de unidades: " << _allocated_outEdges << " (de 0 a " << _allocated_outEdges-1 << ")" << std::endl
                  << " - Indice: " << i << std::endl;
        wait();

        return NULL;
    }

    return _outgoingEdge[i];
}

void Neuron::outputMalloc(int v)
{
    if(_outgoingEdge != NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de saida ja esta alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        wait();
    }

    _outgoingEdge = new Neural_HalfEdge*[v];
    _allocated_outEdges = 0;
    _outHalfedges = v;
}

void Neuron::inputMalloc(int v)
{
    if(_incomingEdges != NULL)
    {
        std::cout << "Neuron: Erro - Memoria para semi-arestas de entrada ja esta alocada." << std::endl;
        std::cout << " - Neuron " << ID << ", camada " << layer->pos() << ";" << std::endl;
        wait();
    }

    _incomingEdges = new Neural_HalfEdge*[v];
    _allocated_inEdges = 0;
    _inHalfedges = v;
}

void Neuron::set_weights(float *weights)
{
    for(int i = 0; i < _allocated_inEdges; ++i)
        _incomingEdges[i]->set_weight(weights[i]);
}

int Neuron::incomingEdges() const {return _allocated_inEdges;}

void Neuron::is_output(bool b) {_is_output = b;}

std::ostream &operator<<(std::ostream &stream, Neuron n)
{
	std::cout << "Neuron " << (n.id() < 10 ? " " : "" ) << n.id() << " ::";

	if(n._outgoingEdge==NULL)
        std::cout << " (Saida)";
	else
	{
        std::cout << " Pesos das arestas: ";

        for(int i = 0; i < n._outHalfedges; ++i)
            std::cout << n._outgoingEdge[i]->head()->id() << ":" << (n._outgoingEdge[i]->weight() >= 0 ? " " : "") << n._outgoingEdge[i]->weight() << " ";
	}

	return stream;
}

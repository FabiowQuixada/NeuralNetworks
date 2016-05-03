#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include "vector.h"


using namespace std;

class Layer;
class Neural_HalfEdge;
typedef std::vector<float> FloatList;

class Neuron
{
	public:
        Neuron();
        Neuron(Layer*);
       ~Neuron();
        int id() const;

        bool  is_output() const;
        Neural_HalfEdge* edgeTo(Neuron*);
        Neural_HalfEdge* edgeFrom(Neuron*) const;
        Neural_HalfEdge* edge(int);
        float activation() const;
        float bias() const;
        float input() const;
        float output() const;

        int incomingEdges() const;
        int outgoingEdges() const;
        Neural_HalfEdge* incomingEdge(int) const;
        Neural_HalfEdge* outgoingEdge(int) const;

        Vector weightVector() const;

        void send_signalIfExcited() const;
        void connectTo(Neuron*);

        void inputMalloc(int); // The number of edges to be allocated;
        void outputMalloc(int); // The number of edges to be allocated;

        void set_bias(float);
        void set_weights(float*);
        void set_activation(float);
        void add_incomingEdge(Neural_HalfEdge*);
        void add_outgoingEdge(Neural_HalfEdge*);
        void addTo_activation(float);
        void addTo_bias(float);
        void addTo_input(float);
        void is_output(bool);

	private:
        int ID;
        static int neuronID;
        int   _pos;
        float _activation;
        float _bias;
        float _input;
        float _output;
        int   _inHalfedges;
        int   _outHalfedges;
        int   _allocated_inEdges;
        int   _allocated_outEdges;
        bool  _is_output;
        Layer *layer;

        Neural_HalfEdge* (*_incomingEdges);
        Neural_HalfEdge* (*_outgoingEdge);
        void setup();

        friend std::ostream &operator<<(std::ostream&,Neuron);
};

#endif // NEURON_H


#ifndef LAYER_H
#define LAYER_H

#include <cstdarg>
#include <iostream>

#include "neuron.h"
#include "halfedge.h"

class NeuralNetwork;

void wait();

class Layer
{
	public:
		Layer(int);   // Sets the number of neurons in the layer;
	    //~Layer();

        int pos() const;
        int length() const;
        Neuron* neuron(int) const;

        void set_network(NeuralNetwork*);    // Sets the corresponding network;
        void connectTo(Layer*);              // Connects each neuron from this layer to each neuron of the given layer;

	private:
        int _length;                         // The number of neuron in the layer;
        Neuron* (*neuronList);
        NeuralNetwork* net;
        int _position;

        friend std::ostream &operator<<(std::ostream&, const Layer);
};

#endif // LAYER_H

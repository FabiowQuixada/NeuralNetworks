#ifndef N_NETWORK_H
#define N_NETWORK_H

#include <fstream>
#include <iostream>
#include <vector>

#include "layer.h"
#include "neuron.h"
#include "pattern.h"
#include "main_functions.h"

using namespace std;

class NeuralNetwork
{
	public:
		NeuralNetwork();

       ~NeuralNetwork();
        int id() const;
        float threshold() const;
        int length() const;

        // Buildings;
        void build(int,int);
        void set_input(Pattern);


        void load(const char *); // Loads the net from a file;
        int* test(Pattern) const;

        void print();
        friend std::ostream &operator<<(std::ostream&, const NeuralNetwork);

	protected:
        int ID;
        static int neuralNetworkID;
        static bool printing;
        float _threshold;
        int _length;           // The number of layers in the net;
        int _allocated_layers; // The number of instantiated layers;
        Layer* (*layers);      // List of layers;


        // Auxiliary methods;
        Layer* layer(int) const;
        void add_layer(Layer*);
        Layer* inputLayer() const;
        Layer* outputLayer() const;
        void set_length(int);


        // Consistency methods;
        bool inputOK(Pattern) const;
        bool outputOK(int) const;
        bool inputOK(PatternList) const;
        bool outputOK(IntList) const;
        bool consistentTrainningPair(PatternList, IntList) const;


};

#endif // N_NETWORK_H

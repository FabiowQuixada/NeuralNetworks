#include "hopfield.h"

void wait();

Hopfield::Hopfield() : NeuralNetwork()
{
    if(_length != 0)
    {
        std::cout << "NeuralNetwork: Erro - Reconstrucao da rede neural.";
        wait();
        return;
    }

    layers = new Layer*[1];

    Layer *layer = new Layer(4);

    add_layer(layer);
    layer->connectTo(layer);
}

void Hopfield::train(Pattern p)
{

    // hebb
    float y_in = 0.0;
    float y;

    do{
        for(int b = 0; b < outputLayer()->length(); ++b)
        {
            // Computes the input of the output unit (the bias has already been added to 'y_in');
            for(int a = 0; a < inputLayer()->length(); ++a)
                y_in += inputLayer()->neuron(a)->activation() * inputLayer()->neuron(a)->edgeTo(outputLayer()->neuron(b))->weight();


            // Applies threshold;
            if(y_in > _threshold)       y =  1;
            else if(y_in < _threshold)  y = 0;
            else                        y =  y_in;

            // broadcast to all others;
        }
    }while(true);
}

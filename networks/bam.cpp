#include "bam.h"

void wait();

BAM::BAM() : NeuralNetwork()
{
    if(_length != 0)
    {
        std::cout << "NeuralNetwork: Erro - Reconstrucao da rede neural.";
        wait();
        return;
    }

    Layer *xLayer = new Layer(3);
    Layer *yLayer = new Layer(3);

    add_layer(xLayer);
    add_layer(yLayer);

    Pattern p;

    NeuronList::iterator it, y_it;
    int y_in = 0;

    for(int a = 0; a < inputLayer()->length(); ++a)
        inputLayer()->neuron(a)->set_activation(p.input(a));

    for(int a = 0; a < outputLayer()->length(); ++a)
        outputLayer()->neuron(a)->set_activation(p.input(a));

    do{
        for(int b = 0; b < outputLayer()->length(); ++b)
            for(int a = 0; a < inputLayer()->length(); ++a)
                y_in += inputLayer()->neuron(a)->activation() * inputLayer()->neuron(a)->edgeTo(outputLayer()->neuron(b))->weight();

        // sned signal;

        for(int b = 0; b < outputLayer()->length(); ++b)
            for(int a = 0; a < inputLayer()->length(); ++a)
                y_in += inputLayer()->neuron(a)->activation() * inputLayer()->neuron(a)->edgeTo(outputLayer()->neuron(b))->weight();

        // send signal;
    }while(true);
}


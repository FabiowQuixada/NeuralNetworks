#include "maxnet.h"

void wait();

MaxNet::MaxNet(int n) : NeuralNetwork()
{
    float e = 0.2;
    Layer *l = new Layer(n);

    set_length(1);

    add_layer(l);

    l->connectTo(l);

    for(int a = 0; a < inputLayer()->length(); ++a)
        for(int b = 0; b < inputLayer()->length(); ++b)
            if(a == b) layer(0)->neuron(a)->edgeTo(layer(0)->neuron(b))->set_weight( 1);
            else       layer(0)->neuron(a)->edgeTo(layer(0)->neuron(b))->set_weight(-e);

    std::cout << *this;
}

float f(float x)
{
    if(x > 0) return x;

    return 0;
}

void MaxNet::train(Pattern p)
{
    bool stop = false;
    /// TODO!!
    int old[4] = {p.input(0), p.input(1), p.input(2), p.input(3)};
    float t = -0.2;

    set_input(p);

    while(!stop)
    {
        for(int a = 0; a < inputLayer()->length(); ++a)
        {
            float sum = 0.0;

            for(int b = 0; b < inputLayer()->length(); ++b)
                if(a != b)
                    sum += old[b];

            std::cout << "s: " << sum;

            inputLayer()->neuron(a)->set_activation(f(old[a] - t*sum));
            //inputLayer()->neuron(a)->completePrint();
            std::cout << "a: " << a << " " << inputLayer()->neuron(a)->activation() << ", soma:" << sum << std::endl;


        }

        for(int a = 0; a < inputLayer()->length(); ++a)
            old[a] = inputLayer()->neuron(a)->activation();

        int k;

        for(int i = 0; i < inputLayer()->length(); ++i)
        {
            std::cout << inputLayer()->neuron(i)->activation() << " ";
            if(inputLayer()->neuron(i)->activation() > 0) ++k;

            if(k > 1)
            {
                stop = true;
                break;
            }
        }

        std::cout << std::endl;
        std::cin >> k;
    }
}

std::ostream &operator<<(std::ostream &output, const MaxNet net)
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

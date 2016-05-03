#include "mexican_hat.h"

void wait();

MexicanHat::MexicanHat(int n, int R1, int R2) : NeuralNetwork()
{
    Layer *l = new Layer(n);
    set_length(1);
    add_layer(l);

    posRadius = R1;
    negRadius = R2;
    negWeight = -0.4;
    posWeight = 0.6;

    for(int a = 0; a < inputLayer()->length(); ++a)
    {
        // Memory allocation for halfedges of the neurons. The initial and final
        // neurons are connected to less neurons, and this is handled here;
        if(a < negRadius)
            inputLayer()->neuron(a)->outputMalloc(a + negRadius + 1);
        else if (a + negRadius >= inputLayer()->length())
            inputLayer()->neuron(a)->outputMalloc(inputLayer()->length()+1 -a + 1);
        else
            inputLayer()->neuron(a)->outputMalloc(2*negRadius + 1);


        // The 'before' negative area;
        for(int r = -negRadius; r <= -posRadius-1; ++r)
        {
            if((a + r >= 0) and (a + r < inputLayer()->length()) and r != 0)
            {
                inputLayer()->neuron(a)->connectTo(inputLayer()->neuron(a+r));
                inputLayer()->neuron(a)->edgeTo(inputLayer()->neuron(a+r))->set_weight(negWeight);
            }
        }


        // The positive area;
        for(int r = -posRadius; r <= posRadius; ++r)
        {
            cout << r << " ";

            if((a + r >= 0) and (a + r < inputLayer()->length()))
            {
                inputLayer()->neuron(a)->connectTo(inputLayer()->neuron(a+r));
                inputLayer()->neuron(a)->edgeTo(inputLayer()->neuron(a+r))->set_weight(posWeight);
            }
        }


        // The 'after' negative area;
        for(int r = posRadius + 1; r <= negRadius; ++r)
        {
            if((a + r >= 0) and (a + r < inputLayer()->length()) and r != 0)
            {
                inputLayer()->neuron(a)->connectTo(inputLayer()->neuron(a+r));
                inputLayer()->neuron(a)->edgeTo(inputLayer()->neuron(a+r))->set_weight(negWeight);
            }
        }
    }
}

void MexicanHat::train(Pattern p)
{
    const int size = 7;

    float t_max = 2;

    float signal[size] = {0.0, 0.5, 0.8, 1.0, 0.8, 0.5, 0.0};
    float x_old[size] = {0};

    for(int i = 0; i < size; ++i)
        x_old[i] = signal[i];


    /**
        ------------------N------------------
        (----- (----------|----------) -----)
        R2 (-) R1 (+)           (+) R1 (-) R2
    */

    for(int t = 0; t <= t_max; ++t)
    {
        cout << endl << " === t = " << t << " ============================" << endl;

        cout << "signal: ";
        for(int i = 0; i < 7; ++i)
                cout << x_old[i] << " ";

        for(int a = 0; a < inputLayer()->length(); ++a)
        {
            cout << endl << endl << a  << ": ";
            float posSum = 0.0, negSum = 0.0;



            // Left negative part;
            for(int k = -negRadius; k <= -posRadius-1; ++k)
                if(a+k >= 0 and a+k < size)
                {

                negSum += x_old[a+k];
                cout << "a yey: " << a+k << ", x_old: " << x_old[a+k] << endl;
                }

            // (Central) positive part;
            for(int k = -posRadius; k <= posRadius; ++k)
            {
                if(a+k >= 0 and a+k < size)
                {
                    posSum += x_old[a+k];
                    cout << "b yey: " << a+k << ", x_old: " << x_old[a+k] << endl;
                }
            }

            // Right negative part;
            for(int k = posRadius; k <= negRadius; ++k)
                if(a+k >= 0 and a+k < size)
                {negSum += x_old[a+k];
                cout << "c yey: " << a+k << ", x_old: " << x_old[a+k] << endl;
        }

                cout << "pos: " << posSum << ", neg: " << negSum << endl;

            inputLayer()->neuron(a)->set_activation(posWeight*posSum + negWeight*negSum);

            for(int a = 0; a < inputLayer()->length(); ++a)
                if(inputLayer()->neuron(a)->activation() < 0)
                    inputLayer()->neuron(a)->set_activation(0);


            for(int a = 0; a < inputLayer()->length(); ++a)
                x_old[a] = inputLayer()->neuron(a)->activation();

        }
    }
}

std::ostream &operator<<(std::ostream &output, const MexicanHat net)
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

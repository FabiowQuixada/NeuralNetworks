#include "lvq.h"

#include <cmath>
void wait();

using namespace std;

LVQ::LVQ(int input, int numberOfClusters) : NeuralNetwork()
{
    if(_length != 0)
    {
        std::cout << "NeuralNetwork: Erro - Reconstrucao da rede neural.";
        wait();
        return;
    }

    set_length(2);

    Layer *xLayer = new Layer(input);
    Layer *yLayer = new Layer(numberOfClusters);

    xLayer->connectTo(yLayer);

    add_layer(xLayer);
    add_layer(yLayer);

    learningRate = 0;

    /// Specific
    learningRate = 0.1;


}

void LVQ::train(PatternList patternList, int* classes)
{
    // There are m clusters and n > m input vectors;

    // Uses the the first m input vector so set each of the output units reference vectors, ie, weight vectors;
    for(int b = 0; b < layer(1)->length(); ++b)
    {
        for(int a = 0; a < inputLayer()->length(); ++a)
        {
            Neuron *n = inputLayer()->neuron(a);

            layer(1)->neuron(b)->edgeFrom(n)->set_weight(patternList.at(b)->input(a));
        }
    }

    do{

        // Uses the remaining (n - m) input vectors to train the net;
        for(int b = layer(1)->length(); b < patternList.size(); ++b)
        {

            float min = 100000.0;
            int winnerIndex = 0;

            // Finds which cluster has its corresponding reference vector closest to the input vector;
            for(int i = 0; i < layer(1)->length(); ++i)
            {
                Vector v1 = layer(1)->neuron(i)->weightVector();
                Vector v2 = patternList.at(b)->toVector();

                float k1 = (v2 - v1).length2();

                if(abs(k1) < min)
                {
                    min = abs(k1);
                    winnerIndex = i;
                }
            }

            // The winning cluster;
            Neuron *n = layer(1)->neuron(winnerIndex);

            float* weights = new float[n->incomingEdges()];

            for(int i = 0; i < n->incomingEdges(); ++i)
            {
                if(classes[b] == winnerIndex)
                    weights[i] = n->incomingEdge(i)->weight() + learningRate*(patternList.at(b)->input(i) - n->incomingEdge(i)->weight());
                else
                    weights[i] = n->incomingEdge(i)->weight() - learningRate*(patternList.at(b)->input(i) - n->incomingEdge(i)->weight());
            }

            n->set_weights(weights);
        }

        learningRate -= 0.1;

    }while(learningRate > 0.1);
}

std::ostream &operator<<(std::ostream &output, const LVQ net)
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

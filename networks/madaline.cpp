#include "madaline.h"

#include <cmath>

void wait();

Madaline::Madaline() : NeuralNetwork()
{
    if(_length != 0)
    {
        std::cout << "NeuralNetwork: Erro - Reconstrucao da rede neural.";
        wait();
        return;
    }

    layers = new Layer*[3];
    _length = 3;

    Layer *inputLayer = new Layer(2),
          *hiddenLayer = new Layer(2),
          *outputLayer = new Layer(1);

    inputLayer->neuron(0)->edge(0)->set_weight(.05);
    inputLayer->neuron(0)->edge(1)->set_weight(.10);
    inputLayer->neuron(1)->edge(0)->set_weight(.20);
    inputLayer->neuron(1)->edge(1)->set_weight(.20);

    hiddenLayer->neuron(0)->edge(0)->set_weight(.50);
    hiddenLayer->neuron(0)->edge(1)->set_weight(.50);

    hiddenLayer->neuron(0)->set_bias(.30);
    hiddenLayer->neuron(1)->set_bias(.15);
    outputLayer->neuron(0)->set_bias(.50);

    inputLayer->connectTo(hiddenLayer);
    hiddenLayer->connectTo(outputLayer);

    add_layer(inputLayer);
    add_layer(hiddenLayer);
    add_layer(outputLayer);
}

void Madaline::apply_madalineRuleI(PatternList patternList, IntList targetList)
{
    // If the size of the input is different from the size of the input Layer of the net, or the size of the target
    // is different from the size of the output layer or if there is not the same number of patterns and outputs;
    if( !inputOK(patternList) or !outputOK(targetList) or !consistentTrainningPair(patternList,targetList)) return;



    PatternList::iterator pattern_it = patternList.begin();
    IntList::iterator target_it = targetList.begin();
    Neuron *output = outputLayer()->neuron(0);
    float learningRate = 0.5;
    int update = 0, maxUpdates = 9;
    bool noUpdate = false;
    _threshold = 0;

    do{
        pattern_it = patternList.begin();
        target_it = targetList.begin();

        // For each pair (input : target), (surely there is the same number of patterns and targets (condition 2) )...
        for(unsigned int k = 0; k < targetList.size(); ++k)
        {
            // For each layer 'l' in the neural network...
            for(int l = 0; l < this->length(); ++l)
            {
                // For each Neuron in the 'l'th layer...
                for(int a = 0; a < layer(l)->length(); ++a)
                {
                    Neuron *n = layer(l)->neuron(a);

                    // Its net-input is computed;
                    n->addTo_input( n->bias() );
                    for(int b = 0; b < inputLayer()->length(); ++b)
                    {
                        Neuron *prev = inputLayer()->neuron(b);

                        prev->set_activation( (*pattern_it)->input(b) );
                        n->addTo_input( prev->activation() * prev->edgeTo(n)->weight() );
                    }

                    std::cout << "Entrada para " << n->id() << ": " << n->input() << std::endl;



                    // Threshold function;
                    if(n->input() >= _threshold)      n->set_activation(1);
                    else if(n->input() < _threshold)  n->set_activation(-1);

                    // Add the ouput of the current neuron to each of its successors' inputs;
                    output->addTo_input( n->activation() * n->edgeTo(output)->weight() );
                }

                std::cout << "Entrada para " << output->id() << ": " << output->input() << std::endl;
            }

            if((*target_it) != output->output())
            {
                ++update;
                if((*target_it)==1)
                {
                    std::cout << "sim" << std::endl;
                    int l = 0;
                    Neuron *closestToZero = layer(l)->neuron(0);
                    HalfEdgeList::iterator halfEdge_it;

                    for(int a = 0; a < layer(l)->length(); ++a)
                        if(std::abs(layer(l)->neuron(a)->input()) < std::abs(closestToZero->input()))
                            closestToZero = layer(l)->neuron(a);

                    closestToZero->addTo_bias( learningRate*(1 - closestToZero->input() ) );

//                    for(halfEdge_it = closestToZero->incomingEdges.begin(); halfEdge_it != closestToZero->incomingEdges.end(); ++halfEdge_it)
//                    {
//                        (*halfEdge_it)->addTo_weight( learningRate*(-1 - closestToZero->input() )*(*halfEdge_it)->tail()->activation() );
//                        //cout << (*halfEdge_it)->weight() << endl;
//                    }
                }
                else if((*target_it)==-1)
                {
                    std::cout << "Nao" << std::endl;
                    int l = 0;
                    HalfEdgeList::iterator halfEdge_it;

                    // For each neuron in the previous layer, if this neuron has positive input...
                    for(int a = 0; a < layer(l)->length(); ++a)
                    {
                        if(std::abs(layer(l)->neuron(a)->input()) > 0)
                        {
                            layer(l)->neuron(a)->addTo_bias( learningRate*(-1 - layer(l)->neuron(a)->input() ) );

                            //cout << n->bias() << endl;

//                            for(halfEdge_it = n->incomingEdges.begin(); halfEdge_it != n->incomingEdges.end(); ++halfEdge_it)
//                            {
//                                (*halfEdge_it)->addTo_weight( learningRate*(-1 - n->input() )*(*halfEdge_it)->tail()->activation() );
//                                //cout << (*halfEdge_it)->weight() << endl;
//                            }
                        }
                    }
                }
            }
            else
                noUpdate = true;

            ++pattern_it;
            ++target_it;

            wait();

        } // END: for each pair;

        wait();
    }while(!noUpdate or (update > maxUpdates));
}


#include "delta.h"

void wait();

Delta::Delta(int i, int o) : NeuralNetwork()
{
    if(_length != 0)
    {
        std::cout << "NeuralNetwork: Erro - Reconstrucao da rede neural.";
        wait();
        return;
    }

    layers = new Layer*[2];
    _length = 2;

    Layer *layer1 = new Layer(i),
          *layer2 = new Layer(o);

    layer1->connectTo(layer2);

    add_layer(layer1);
    add_layer(layer2);
}


void Delta::apply_delta(PatternList patternList, IntList targetList)
{
    // If the size of the input is different from the size of the input Layer of the net, or the size of the target
    // is different from the size of the output layer or if there is not the same number of patterns and outputs;
    if( !inputOK(patternList) or !outputOK(targetList) or !consistentTrainningPair(patternList,targetList) ) return;



    PatternList::iterator pattern_it = patternList.begin();
    IntList::iterator target_it = targetList.begin();
    Neuron *output = outputLayer()->neuron(0);
    float learningRate =  0.1;
    float y_in = output->bias();
    float largestChange = 0.0;
    float tolerance = 0.0001;
    int y = 0;
    int f = 0;

    do{
        if(printing) std::cout << "  ~ (" << f++ << ") ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        pattern_it = patternList.begin();
        target_it = targetList.begin();
        largestChange = 0.0;

        // For each pair (input : target), (surely there is the same number of patterns and targets (condition 2) )...
        for(unsigned int k = 0; k < targetList.size(); ++k)
        {
            // Sets activations of input units and computes the net input to output unit;
            for(int a = 0; a < inputLayer()->length(); ++a)
            {
                inputLayer()->neuron(a)->set_activation( (*pattern_it)->input(a) );
                y_in += inputLayer()->neuron(a)->activation() * inputLayer()->neuron(a)->edgeTo(output)->weight();
            }

            // Applies threshold;
            if(y_in >= 0) y =  1;
            else          y = -1;


            // Updates weights;
            for(int a = 0; a < inputLayer()->length(); ++a)
            {
                float change = learningRate * ((*target_it) - y) * inputLayer()->neuron(a)->activation();
                inputLayer()->neuron(a)->edgeTo(output)->addTo_weight(change);

                if(change > largestChange) largestChange = change;
            }

            // Updates the current output unit's bias;
            output->addTo_bias( learningRate * ( (*target_it) - y) );

            if(printing) (*pattern_it)->print();
            if(printing) std::cout << "   1";
            if(printing) std::cout << "     " << ( y >= 0 ? " " : "") << y << "   ";
            if(printing) std::cout << "     " << ( (*target_it) >= 0 ? " " : "") << (*target_it) << "         ";
            if(printing) for(int a = 0; a < inputLayer()->length(); ++a) std::cout << ( inputLayer()->neuron(a)->edgeTo(output)->weight() >= 0 ? " " : "") << inputLayer()->neuron(a)->edgeTo(output)->weight() << "  ";
            if(printing) std::cout << output->bias();
            if(printing) std::cout << std::endl;

            // Next pair...
            pattern_it++;
            target_it++;
        }

        std::cout << largestChange; wait();
    }while(largestChange > tolerance);
}

void Delta::delta(Pattern p, int target)
{
    // If the size of the input is different from the size of the input Layer of the net, or the size of the target
    // is different from the size of the output layer or if there is not the same number of patterns and outputs;
    if( !inputOK(p) or !outputOK(target) ) return;
}

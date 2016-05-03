#include "perceptron.h"

void wait();

Perceptron::Perceptron(int i, int o) : NeuralNetwork()
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


bool Perceptron::train(Pattern p, int target)
{
    // If the size of the input is different from the size of the input Layer of the
    // net, or the size of the target is different from the size of the output layer;
    if( !inputOK(p) or !outputOK(target) ) return false;


    int y = 0;
    float learningRate = 1.0;
    Neuron *output = outputLayer()->neuron(0);
    float y_in = output->bias();


    set_input(p);

    // Computes the input of the output unit (the bias has already been added to 'y_in');
    for(int a = 0; a < inputLayer()->length(); ++a)
        y_in += inputLayer()->neuron(a)->activation() * inputLayer()->neuron(a)->edgeTo(output)->weight();


    // Applies threshold;
    if(y_in > _threshold)        y =  1;
    else if(y_in < -_threshold)  y = -1;
    else                         y =  0;


    // If the input of the output unit is different from the expected value
    // (i.e., the target value), the weights and bias are updated;
    if(y != target)
    {
        output->addTo_bias( learningRate * target );


        for(int a = 0; a < inputLayer()->length(); ++a)
            inputLayer()->neuron(a)->edgeTo(output)->addTo_weight( learningRate * target * inputLayer()->neuron(a)->activation() );

        if(printing) p.print();
        if(printing) std::cout << "   1";
        if(printing) std::cout << "     " << ( y >= 0 ? " " : "") << y << "   ";
        if(printing) std::cout << "     " << ( target >= 0 ? " " : "") << target << "         ";
        if(printing) for(int a = 0; a < inputLayer()->length(); ++a) std::cout << ( inputLayer()->neuron(a)->edgeTo(output)->weight() >= 0 ? " " : "") << inputLayer()->neuron(a)->edgeTo(output)->weight() << "  ";
        if(printing) std::cout << output->bias();
        if(printing) std::cout << std::endl;

        // The weights have changed;
        return true;
    }

    if(printing) p.print();
    if(printing) std::cout << "   1";
    if(printing) std::cout << "     " << ( y >= 0 ? " " : "") << y << "   ";
    if(printing) std::cout << "     " << ( target >= 0 ? " " : "") << target << "         ";
    if(printing) for(int a = 0; a < inputLayer()->length(); ++a) std::cout << ( inputLayer()->neuron(a)->edgeTo(output)->weight() >= 0 ? " " : "") << inputLayer()->neuron(a)->edgeTo(output)->weight() << "  ";
    if(printing) std::cout << output->bias();
    if(printing) std::cout << std::endl;

    // The weights have not changed;
    return false;
}

void Perceptron::train(PatternList patternList, IntList targetList)
{
    // If the size of the input is different from the size of the input Layer of the net, or the size of the target
    // is different from the size of the output layer or if there is not the same number of patterns and outputs;
    if( !inputOK(patternList) or !outputOK(targetList) or !consistentTrainningPair(patternList,targetList) ) return;



    if(printing) std::cout << std::endl << std::endl;
    if(printing) std::cout << " == PERCEPTRON LEARNING RULE =========================== " << std::endl;
    if(printing) std::cout << "  -INPUT-----   -OUTPUT-  -TARGET-   -WEIGHT-------" << std::endl;

    for(PatternList::iterator pattern_it = patternList.begin(); pattern_it != patternList.end(); ++pattern_it)
        train(**pattern_it, targetList);

    if(printing) std::cout << " ======================================================= " << std::endl;
    if(printing) std::cout << std::endl << std::endl;
}

void Perceptron::train(Pattern p, IntList targetList)
{
    // If the size of the input is different from the size of the input Layer of the net, or the size of the target
    // is different from the size of the output layer or if there is not the same number of patterns and outputs;
    if( !inputOK(p) or !outputOK(targetList)) return;



    IntList::iterator target_it = targetList.begin();
    bool result;
    bool changed;
    int outputNumber = 0;
    _threshold = 0;

    // Sets the bias of each output unit;
    for(int b = 0; b < outputLayer()->length(); ++b)
        outputLayer()->neuron(b)->set_bias( 0.0 );

    if(printing) std::cout << std::endl << std::endl;
    if(printing) std::cout << " == PERCEPTRON LEARNING RULE =========================== " << std::endl;
    if(printing) std::cout << "  -INPUT-----   -OUTPUT-  -TARGET-   -WEIGHT-------" << std::endl;

    do{
        target_it = targetList.begin();
        Neuron *output = outputLayer()->neuron(0);

        // For each target (or, equivalently, for each output unit)...
        for(unsigned int t = 0; t < targetList.size(); ++t)
        {
            int i = 0;
            int y = 0;
            float learningRate = 1.0;
            float y_in = output->bias();

            if(printing) std::cout << "  ~ OUTPUT " << outputNumber << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            if(printing) std::cout << "  ~ (" << i << ") ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

            outputNumber++;
            i++;
            changed = false;

            set_input(p);

            // Computes the input of the output unit (the bias has already been added to 'y_in');
            for(int a = 0; a < inputLayer()->length(); ++a)
                y_in += inputLayer()->neuron(a)->activation() * inputLayer()->neuron(a)->edgeTo(output)->weight();


            // Applies threshold;
            if(y_in > _threshold)        y =  1;
            else if(y_in < -_threshold)  y = -1;
            else                         y =  0;


            // If the input of the output unit is different from the expected value
            // (i.e., the target value), the weights and bias are updated;
            if(y != (*target_it))
            {
                output->addTo_bias( learningRate * (*target_it) );

                for(int a = 0; a < inputLayer()->length(); ++a)
                    inputLayer()->neuron(a)->edgeTo(output)->addTo_weight( learningRate * (*target_it) * inputLayer()->neuron(a)->activation() );

                if(printing) p.print();
                if(printing) std::cout << "   1";
                if(printing) std::cout << "     " << ( y >= 0 ? " " : "") << y << "   ";
                if(printing) std::cout << "     " << ( (*target_it) >= 0 ? " " : "") << (*target_it) << "         ";
                if(printing) for(int a = 0; a < inputLayer()->length(); ++a) std::cout << ( inputLayer()->neuron(a)->edgeTo(output)->weight() >= 0 ? " " : "") << inputLayer()->neuron(a)->edgeTo(output)->weight() << "  ";
                if(printing) std::cout << output->bias();
                if(printing) std::cout << std::endl;

                // The weights have changed;
                result =  true;
            }

            if(printing) p.print();
            if(printing) std::cout << "   1";
            if(printing) std::cout << "     " << ( y >= 0 ? " " : "") << y << "   ";
            if(printing) std::cout << "     " << ( (*target_it) >= 0 ? " " : "") << (*target_it) << "         ";
            if(printing) for(int a = 0; a < inputLayer()->length(); ++a) std::cout << ( inputLayer()->neuron(a)->edgeTo(output)->weight() >= 0 ? " " : "") << inputLayer()->neuron(a)->edgeTo(output)->weight() << "  ";
            if(printing) std::cout << output->bias();
            if(printing) std::cout << std::endl;

            // The weights have not changed;
            result = false;

            // If at least one of the results has changed, the loop continues;
            if(result) changed = true;

            // The number of targets and output units is the same, because
            // of the outputOK() checking at the beginning of the method;
            ++target_it;
            ++output;
        }

    }while(changed);

    if(printing) std::cout << " ======================================================= " << std::endl;
    if(printing) std::cout << std::endl << std::endl;
}


std::ostream &operator<<(std::ostream &output, const Perceptron net)
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


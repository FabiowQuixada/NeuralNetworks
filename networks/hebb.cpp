#include "hebb.h"

void wait();

HebbNet::HebbNet(int i, int o) : NeuralNetwork()
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

HebbNet::HebbNet(const char *fileName) {load(fileName);}

void HebbNet::train(Pattern p, int target)
{
    // If the size of the input is different from the size of the input Layer of the
    // net, or the size of the target is different from the size of the output layer;
    if( !inputOK(p) or !outputOK(target) )
    {
        std::cout << "Tamanhos diferentes";
        return;
    }

    // The first (only) neuron in the output layer;
    Neuron *outputNeuron = outputLayer()->neuron(0);

    outputNeuron->set_activation(target);
    outputNeuron->set_bias( 1 + outputNeuron->activation() );

    // For each neuron in the input layer...
    for(int a = 0; a < inputLayer()->length(); ++a)
    {
        // ...set its activation and weight of its edge;
        inputLayer()->neuron(a)->set_activation( p.input(a) );
        inputLayer()->neuron(a)->edgeTo(outputNeuron)->addTo_weight(  inputLayer()->neuron(a)->activation() * outputNeuron->activation()  );
    }

    if(printing) p.print();
    if(printing) std::cout << target;
    if(printing)
        for(int a = 0; a < inputLayer()->length(); ++a)
            std::cout << inputLayer()->neuron(a)->edgeTo(outputNeuron)->weight();
}

void HebbNet::train(PatternList patternList, IntList targetList)
{
    // If the size of the input is different from the size of the input Layer of the net, or the size of the target
    // is different from the size of the output layer or if there is not the same number of patterns and outputs;
    if( !inputOK(patternList) or !outputOK(targetList) or !consistentTrainningPair(patternList,targetList) ) return;


    PatternList::iterator pattern_it;
    IntList::iterator      target_it = targetList.begin();

    if(printing) std::cout << std::endl << std::endl;
    if(printing) std::cout << " == HEBB LEARNING RULE ===================== " << std::endl;
    if(printing) std::cout << "  INPUTS   TARGETS   WEIGHTS" << std::endl;

    for(pattern_it = patternList.begin(); pattern_it != patternList.end(); ++pattern_it)
        train(**pattern_it, *target_it++);

    if(printing) std::cout << " =========================================== " << std::endl;
    if(printing) std::cout << std::endl << std::endl;
}

void HebbNet::train(Pattern p, IntList targetList)
{
    // If the size of the input is different from the size of the input layer of the
    // net, or the size of the target is different from the size of the output layer;
    if( !inputOK(p) or !outputOK(targetList) ) return;


    IntList::iterator target_it = targetList.begin();

    // For each target (or, equivalently, for each output unit)...
    for(unsigned int t = 0; t < targetList.size(); ++t)
    {
        Neuron *output = outputLayer()->neuron(t);

        output->set_activation(*target_it);
        output->set_bias( 1 + output->activation() );


        for(int a = 0; a < inputLayer()->length(); ++a)
        {
            inputLayer()->neuron(a)->set_activation( p.input(a) );
            inputLayer()->neuron(a)->edgeTo(output)->addTo_weight(  inputLayer()->neuron(a)->activation() * (output->activation())  );
        }

        // The number of targets and output units is the same, because
        // of the outputOK() checking at the beginning of the method;
        ++target_it;
    }

    if(printing) std::cout << "Padrao: ";
    if(printing) p.print();
    if(printing) std::cout << std::endl << "Alvos: ";
    if(printing)
        for(target_it = targetList.begin(); target_it != targetList.end(); ++target_it)
            std::cout << *target_it << " ";
    if(printing) std::cout << std::endl << "Pesos: ";
    if(printing)
        for(int b = 0; b < outputLayer()->length(); ++b)
        {
            std::cout << outputLayer()->neuron(b)->id() << ": ";
            for(int a = 0; a < inputLayer()->length(); ++a)
                std::cout << inputLayer()->neuron(a)->edgeTo(outputLayer()->neuron(b))->weight() << " ";
            std::cout << std::endl;
        }

    if(printing) std::cout << std::endl << std::endl;
}

std::ostream &operator<<(std::ostream &output, const HebbNet net)
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

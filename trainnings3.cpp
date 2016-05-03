#include "neural_network.h"
#include "pattern.h"
#include "main_functions.h"

#include <iostream>

#include "networks/mexican_hat.h"
#include "networks/hebb.h"
#include "networks/maxnet.h"

void maxNet()
{
    MaxNet net(4);

    Pattern p;
    IntList aux;

    aux.push_back(1);
    aux.push_back(0.4);
    aux.push_back(0.6);
    aux.push_back(0.8);

    p.populate(aux);

    net.train(p);
}

void mexicanHat()
{
    Pattern p;

    MexicanHat mh(7,1,2);
    mh.train(p);
    cout << mh;
}

void heteroassociative()
{
    // Page 116, Example 3.7;
    HebbNet net(4,2);

    Pattern patternA = input1(),
            patternB = input2(),
            patternC = input3(),
            patternD = input4();

    IntList outputA = output1(),
            outputB = output2(),
            outputC = output3(),
            outputD = output4();

    patternA.set_dimensions(4,1);
    patternB.set_dimensions(4,1);
    patternC.set_dimensions(4,1);
    patternD.set_dimensions(4,1);

    net.train(patternA,outputA);
    net.train(patternB,outputB);
    net.train(patternC,outputC);
    net.train(patternD,outputD);

    std::cout << net;
}

void autoassociative()
{


}

void hopfield()
{
    NeuralNetwork net;
    Pattern p;
//    p.add_input( 1);
//    p.add_input( 1);
//    p.add_input( 1);
//    p.add_input(-1);


    //net.apply_hopfield(p);

    std::cout << net;
}

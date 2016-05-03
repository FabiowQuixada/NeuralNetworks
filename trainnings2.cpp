#include "neural_network.h"
#include "pattern.h"
#include "main_functions.h"

#include "networks/hebb.h"
#include "networks/perceptron.h"
#include "networks/madaline.h"
#include "networks/delta.h"

#include <iostream>

void simpleHebb()
{
    // Page 55;
    HebbNet net("networkstxt/hebb.txt");

    Pattern p1("letters_5by5/x.txt"),
            p2("letters_5by5/o.txt"),
            p3("letters_5by5/c.txt");

    p1.set_dimensions(5,5);
    p2.set_dimensions(5,5);
    p3.set_dimensions(5,5);

    std::cout << "Padrão de treinamento (x): " << std::endl << p1;
    std::cout << "Padrão de treinamento (o): " << std::endl << p2;
    std::cout << "Padrão de teste: " << std::endl << p3;

    net.train(p1,1);
    net.train(p2,-1);


    std::cout << std::endl << "Treino de X: "; net.test(p1);
    std::cout << std::endl << "Treino de O: "; net.test(p2);
    std::cout << std::endl << "Treino de C: "; net.test(p3);

    std::cout << net;
}

void perceptron1()
{
    Perceptron net(4,1);

    PatternList patternList = BIPOLAR_INPUT();
    IntList outputList = AND();

    net.train(patternList, outputList);
}

void perceptron2()
{
    Perceptron net(25,1);

    Pattern patternO("letters_5by5/o.txt"),
            patternX("letters_5by5/x.txt"),
            patternC("letters_5by5/c.txt");

    patternC.set_dimensions(5,5);
    patternO.set_dimensions(5,5);
    patternX.set_dimensions(5,5);

    net.train(patternO, 1);
    net.train(patternX, -1);
    net.test(patternO);
    net.test(patternX);
    net.test(patternC);
}

void perceptron3()
{
    Perceptron net(63,7);

    Pattern patternA("letters_7by9/1a.txt"),
            patternB("letters_7by9/1b.txt"),
            patternC("letters_7by9/1c.txt"),
            patternD, patternE, patternJ, patternK, patternO, patternX, patternA2;

    // Outputs;
    IntList outputA = A(),
            outputB = B(),
            outputC = C(),
            outputD = D(),
            outputE = E(),
            outputJ = J(),
            outputK = K();



    // Patterns (inputs) for font 1;
    patternA.set_dimensions(7,9);
    patternB.set_dimensions(7,9);
    patternC.set_dimensions(7,9);
//    patternD = toBipolar("letters_7by9/1d.txt"); patternD.set_dimensions(7,9);
//    patternE = toBipolar("letters_7by9/1e.txt"); patternE.set_dimensions(7,9);
//    patternJ = toBipolar("letters_7by9/1j.txt"); patternJ.set_dimensions(7,9);
//    patternK = toBipolar("letters_7by9/1k.txt"); patternK.set_dimensions(7,9);
//    patternA2 = toBipolar("letters_7by9/2a.txt"); patternK.set_dimensions(7,9);
//
//
//    cout << patternA;
//
    // Network training for font 1;
    net.train(patternA, outputA);
    net.train(patternB, outputB);
    net.train(patternC, outputC);
//    net.train(patternD, outputD);
//    net.train(patternE, outputE);
//    net.train(patternJ, outputJ);
//    net.train(patternK, outputK);

    // Patterns (inputs) for font 2;
//    patternA = toBipolar("letters_7by9/2a.txt");
//    patternB = toBipolar("letters_7by9/2b.txt");
//    patternC = toBipolar("letters_7by9/2c.txt");
//    patternD = toBipolar("letters_7by9/2d.txt");
//    patternE = toBipolar("letters_7by9/2e.txt");
//    patternJ = toBipolar("letters_7by9/2j.txt");
//    patternK = toBipolar("letters_7by9/2k.txt");

    // Network training for font 2;
//    net.train(patternA, outputA);
//    net.train(patternB, outputB);
//    net.train(patternC, outputC);
//    net.train(patternD, outputD);
//    net.train(patternE, outputE);
//    net.train(patternJ, outputJ);
//    net.train(patternK, outputK);
//
//
    // Patterns (inputs) for font 3;
//    patternA = toBipolar("letters_7by9/3a.txt");
//    patternB = toBipolar("letters_7by9/3b.txt");
//    patternC = toBipolar("letters_7by9/3c.txt");
//    patternD = toBipolar("letters_7by9/3d.txt");
//    patternE = toBipolar("letters_7by9/3e.txt");
//    patternJ = toBipolar("letters_7by9/3j.txt");
//    patternK = toBipolar("letters_7by9/3k.txt");

    // Network training for font 3;
    net.train(patternA, outputA);
    net.train(patternB, outputB);
    net.train(patternC, outputC);
//    net.train(patternD, outputD);
//    net.train(patternE, outputE);
//    net.train(patternJ, outputJ);
//    net.train(patternK, outputK);

    std::cout << "A:" << std::endl; net.test(patternA);
    std::cout << "B:" << std::endl; net.test(patternB);
    std::cout << "C:" << std::endl; net.test(patternC);
//    cout << "D:" << endl; net.test(patternA2);
//    cout << "E:" << endl; net.test(patternE);
//    cout << "J:" << endl; net.test(patternJ);
//    cout << "K:" << endl; net.test(patternK);
}

void delta()
{
    Delta net(2,1);

    PatternList patternList = BIPOLAR_INPUT();
    IntList outputList = AND();

    net.apply_delta(patternList, outputList);
}

void MRI()
{
    Madaline net;

    PatternList patternList = BIPOLAR_INPUT();
    IntList outputList = XOR();

    net.apply_madalineRuleI(patternList,outputList);
}


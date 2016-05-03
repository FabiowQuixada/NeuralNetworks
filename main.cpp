
/// Functions;
void heteroassociative();
void simpleHebb();
void perceptron1();
void perceptron2();
void perceptron3();
void delta();
void MRI();
void hopfield();
void maxNet();
void mexicanHat();
void LVQa();

#include "neural_network.h"
#include "networks/hebb.h"

int main(int argc, char **argv)
{
    int way = 41;

    switch(way)
    {
        // Hebb;
        case 00: simpleHebb(); break;
        case 01: heteroassociative(); break;

        // Perceptron;
        case 10: perceptron1(); break;
        case 11: perceptron2(); break;
        case 12: perceptron3(); break;

        // Delta;
        case 20: delta(); break;
        case 21: MRI(); break;

        case 30: hopfield(); break;
        case 31: maxNet(); break;
        case 32: mexicanHat(); break;

        case 41: LVQa(); break;

        default: break;
    }
}

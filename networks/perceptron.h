#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "../neural_network.h"

class Perceptron : public NeuralNetwork
{
    public:
        Perceptron(int,int);

        bool train(Pattern, int);
        void train(Pattern, IntList);
        void train(PatternList, IntList);

        friend std::ostream &operator<<(std::ostream&, const Perceptron);
        friend class NeuralNetwork;
};

#endif // PERCEPTRON_H


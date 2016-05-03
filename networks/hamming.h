#ifndef HAMMING_H
#define HAMMING_H

#include "../neural_network.h"

class Hamming : public NeuralNetwork
{
    public:
        Hamming();

        void train(Pattern);

        friend std::ostream &operator<<(std::ostream&, const Hamming);
        friend class NeuralNetwork;
};

#endif // HAMMING_H


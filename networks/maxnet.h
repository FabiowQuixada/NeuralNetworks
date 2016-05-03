#ifndef MAXNET_H
#define MAXNET_H

#include "../neural_network.h"

class MaxNet : protected NeuralNetwork
{
    public:
        MaxNet(int);

        void train(Pattern);

        friend std::ostream &operator<<(std::ostream&, const MaxNet);
        friend class NeuralNetwork;
};

#endif // MAXNET_H


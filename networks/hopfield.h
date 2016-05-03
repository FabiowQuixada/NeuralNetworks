#ifndef HOPFIELD_H
#define HOPFIELD_H

#include "../neural_network.h"

class Hopfield : public NeuralNetwork
{
    public:
        Hopfield();

        void train(Pattern);

        friend std::ostream &operator<<(std::ostream&, const Hopfield);
        friend class NeuralNetwork;
};

#endif // HOPFIELD_H


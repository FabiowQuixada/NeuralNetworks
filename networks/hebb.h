#ifndef HEBB_H
#define HEBB_H

#include "../neural_network.h"

class HebbNet : public NeuralNetwork
{
    public:
        HebbNet(int,int);
        HebbNet(const char *);

        // Hebb Learning Rule;
        void train(Pattern, int);
        void train(Pattern, IntList);
        void train(PatternList, IntList);

        friend std::ostream &operator<<(std::ostream&, const HebbNet);
        friend class NeuralNetwork;
};

#endif // HEBB_H


#ifndef DELTA_H
#define DELTA_H

#include "../neural_network.h"

class Delta : public NeuralNetwork
{
    public:
        Delta(int,int);

        void train(Pattern, int);
        void train(Pattern, IntList);
        void train(PatternList, IntList);

        // Delta Learning Rule;
        void delta(Pattern p, int target); /// TODO!!
        void apply_delta(PatternList, IntList);

        friend std::ostream &operator<<(std::ostream&, const Delta);
        friend class NeuralNetwork;
};

#endif // DELTA_H

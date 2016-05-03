#ifndef LVQ_H
#define LVQ_H

#include "../neural_network.h"

class LVQ : public NeuralNetwork
{
    public:
        LVQ(int, int);

        void train(PatternList, int*);

        friend std::ostream &operator<<(std::ostream&, const LVQ);

        friend class NeuralNetwork;

    private:

        float learningRate;

};

#endif // LVQ_H


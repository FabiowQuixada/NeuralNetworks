#ifndef BAM_H
#define BAM_H

#include "../neural_network.h"

class BAM : public NeuralNetwork
{
    public:
        BAM();

        void train(Pattern, int);
        void train(Pattern, IntList);
        void train(PatternList, IntList);

        friend std::ostream &operator<<(std::ostream&, const BAM);

        friend class NeuralNetwork;
};

#endif // BAM_H


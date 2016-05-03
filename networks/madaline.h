#ifndef MADALINE_H
#define MADALINE_H

#include "../neural_network.h"

using namespace std;

class Madaline : public NeuralNetwork
{
    public:
        Madaline();

        void train(Pattern, int);
        void train(Pattern, IntList);
        void train(PatternList, IntList);

        // Madaline Learning Rules;
        void apply_madalineRuleI(PatternList, IntList); /// TODO!!
        void apply_madalineRuleII(PatternList, IntList); /// TODO!!!

        friend std::ostream &operator<<(std::ostream&, const Madaline);
        friend class NeuralNetwork;
};

#endif // MADALINE_H


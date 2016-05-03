#ifndef MEXICAN_HAT_H
#define MEXICAN_HAT_H

#include "../layer.h"
#include "../neural_network.h"

class MexicanHat : protected NeuralNetwork
{
    public:
        MexicanHat(int neurons, int R1, int R2);
        void train(Pattern);

        friend std::ostream &operator<<(std::ostream&, const MexicanHat);
        friend class NeuralNetwork;

    private:
        int posRadius;
        int negRadius;
        float negWeight;
        int posWeight;
};

#endif // MEXICAN_HAT_H


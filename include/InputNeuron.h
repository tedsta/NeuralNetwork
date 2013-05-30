#ifndef INPUTNEURON_H
#define INPUTNEURON_H

#include "Neuron.h"

class InputNeuron : public Neuron
{
    public:
        InputNeuron();
        virtual ~InputNeuron();

        virtual float simulate();

    private:
};

#endif // INPUTNEURON_H

#ifndef ACTIVATIONNEURON_H
#define ACTIVATIONNEURON_H

#include "Neuron.h"

class ActivationNeuron : public Neuron
{
    public:
        ActivationNeuron();
        virtual ~ActivationNeuron();

        virtual void calculateInput();
        virtual float simulate();

    private:
};

#endif // ACTIVATIONNEURON_H

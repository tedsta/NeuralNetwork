#ifndef BIASNEURON_H
#define BIASNEURON_H

#include "Neuron.h"

class BiasNeuron : public Neuron
{
    public:
        BiasNeuron();
        virtual ~BiasNeuron();

        virtual void calculateInput();
        virtual float simulate();

    protected:
    private:
};

#endif // BIASNEURON_H

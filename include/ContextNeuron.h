#ifndef CONTEXTNEURON_H
#define CONTEXTNEURON_H

#include "Neuron.h"

class ContextNeuron : public Neuron
{
    public:
        ContextNeuron(Neuron *base);
        virtual ~ContextNeuron();

        virtual void calculateInput();
        virtual float simulate();
        virtual void postSimulate();

        // Accessors
        Neuron *getBase(){return mBase;}

        // Mutators
        void setBase(Neuron *base){mBase=base;}

    private:
        Neuron *mBase; // Who do I copy from?
};

#endif // CONTEXTNEURON_H

#include "ContextNeuron.h"

ContextNeuron::ContextNeuron(Neuron *base) : mBase(base)
{
    //ctor
}

ContextNeuron::~ContextNeuron()
{
    //dtor
}

void ContextNeuron::calculateInput()
{
}

float ContextNeuron::simulate()
{
    mOutput = mInput; // The output is the only input
    return mOutput;
}

void ContextNeuron::postSimulate()
{
    mInput = mBase->getOutput();
}

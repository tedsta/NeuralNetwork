#include "BiasNeuron.h"

BiasNeuron::BiasNeuron()
{
    //ctor
}

BiasNeuron::~BiasNeuron()
{
    //dtor
}

void BiasNeuron::calculateInput()
{
}

float BiasNeuron::simulate()
{
    mOutput = 1.f; // Bias neurons always output 1

    return mOutput;
}

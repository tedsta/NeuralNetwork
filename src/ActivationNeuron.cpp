#include "ActivationNeuron.h"

#include <cmath>

ActivationNeuron::ActivationNeuron()
{
    //ctor
}

ActivationNeuron::~ActivationNeuron()
{
    //dtor
}

void ActivationNeuron::calculateInput()
{
    mInput = 0.0f;
    for (std::vector<Connection>::iterator it = mConnections.begin(); it != mConnections.end(); it++)
    {
        mInput += (*it).getSender()->getOutput()*(*it).getWeight();
    }
}

float ActivationNeuron::simulate()
{
    mOutput = 1.f/(1.f+exp(-mInput));

    return mOutput;
}

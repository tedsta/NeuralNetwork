#include "Neuron.h"

#include <cstdlib>
#include <iostream>

Neuron::Neuron() : mInput(0), mOutput(0), mDelta(0)
{
    //ctor
}

Neuron::~Neuron()
{
    //dtor
}

void Neuron::randomizeWeights(float min, float max)
{
    int imin = min*1000.f;
    int imax = max*1000.f;
    for (std::vector<Connection>::iterator it = mConnections.begin(); it != mConnections.end(); it++) // For each connection
    {
        // calculate random weight
        float weight = static_cast<float>((rand()%(imax-imin))+imin)/1000.f;
        (*it).setWeight(weight);
    }
}

float Neuron::calculateDeltaSum(Neuron *sender)
{
    float sum = 0.f;
    for (std::vector<Connection>::iterator it = mConnections.begin(); it != mConnections.end(); it++)
    {
        if ((*it).getSender() == sender)
            sum += mDelta*(*it).getWeight();
    }
    return sum;
}

void Neuron::adjustWeights(float learningRate)
{
    for (std::vector<Connection>::iterator it = mConnections.begin(); it != mConnections.end(); it++)
    {
        (*it).adjustWeight(learningRate * mDelta * (*it).getSender()->getOutput());
    }
}

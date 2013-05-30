#include "InputNeuron.h"

InputNeuron::InputNeuron()
{
    //ctor
}

InputNeuron::~InputNeuron()
{
    //dtor
}

float InputNeuron::simulate()
{
    mOutput = mInput;
    return mOutput;
}

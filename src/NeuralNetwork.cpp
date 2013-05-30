#include "NeuralNetwork.h"

#include <iostream>

#include "Neuron.h"
#include "InputNeuron.h"
#include "ActivationNeuron.h"
#include "ContextNeuron.h"
#include "BiasNeuron.h"

NeuralNetwork::NeuralNetwork() : mLearningRate(0.7f), mPropagateToInput(false), mLastInput(NULL)
{
    //ctor
}

NeuralNetwork::~NeuralNetwork()
{
    // Delete all of the neurons
    for (LayerIterator i = mNeurons.begin(); i != mNeurons.end(); i++)
        for (NeuronIterator j = (*i).begin(); j != (*i).end(); j++)
            delete (*j);
}

void NeuralNetwork::createContextLayer(int baseLayer)
{
    std::vector <Neuron*> layer;
    for (NeuronIterator i = mNeurons[baseLayer].begin(); i != mNeurons[baseLayer].end(); i++)
    {
        ContextNeuron *context = new ContextNeuron((*i));
        layer.push_back(context);
        (*i)->addConnection(Connection(context));
    }
    mNeurons.insert(mNeurons.begin()+baseLayer, layer);
}

void NeuralNetwork::connectLayerFully(int sendLayer, int receiveLayer)
{
    for (unsigned int i = 0; i < mNeurons[sendLayer].size(); i++)
    {
        for (unsigned int j = 0; j < mNeurons[receiveLayer].size(); j++)
        {
            mNeurons[receiveLayer][j]->addConnection(Connection(mNeurons[sendLayer][i]));
        }
    }
}

void NeuralNetwork::randomizeWeights(float min, float max)
{
    for (LayerIterator i = mNeurons.begin(); i != mNeurons.end(); i++)
    {
        for (NeuronIterator j = (*i).begin(); j != (*i).end(); j++)
        {
            (*j)->randomizeWeights(min, max);
        }
    }
}

float *NeuralNetwork::simulate(float *inputs)
{
    // Store the pointer to the input if we want to propagate to the inputs
    if (mPropagateToInput)
        mLastInput = inputs;
    else // Otherwise, the last input can be null.
        mLastInput = NULL;

    // Our array of return values
    float *out = new float[mNeurons.back().size()-1];

    // Handle the input layer, which just so happens to be the first layer :)
    for (NeuronIterator it = mNeurons.front().begin(); it != mNeurons.front().end(); it++) // Iterate through neurons in input layer
    {
        (*it)->setInput(inputs[std::distance(mNeurons.front().begin(), it)]);
    }

    // Simulate all of the layers
    for (LayerIterator i = mNeurons.begin(); i != mNeurons.end(); i++)
    {
        for (NeuronIterator j = (*i).begin(); j != (*i).end(); j++)
        {
            (*j)->calculateInput();
            (*j)->simulate();
        }
    }

    // Call the post-simulation callbacks for all the neurons
    for (LayerIterator i = mNeurons.begin(); i != mNeurons.end(); i++)
    {
        for (NeuronIterator j = (*i).begin(); j != (*i).end(); j++)
        {
            (*j)->postSimulate();
        }
    }

    // Set the output array
    for (NeuronIterator it = mNeurons.back().begin(); it != mNeurons.back().end(); it++)
    {
        out[std::distance(mNeurons.back().begin(), it)] = (*it)->getOutput();
    }

    return out;
}

void NeuralNetwork::backpropTrain(const float *trainOutput)
{
    // Calculate delta for output layer
    for (NeuronIterator it = mNeurons.back().begin(); it != mNeurons.back().end(); it++)
    {
        int index = std::distance(mNeurons.back().begin(), it); // Grab the index of the current output neuron
        float delta = (*it)->getOutput() * (1.f-(*it)->getOutput()) * (trainOutput[index]-(*it)->getOutput()); // Calculate delta
        (*it)->setDelta(delta); // Set the delta
    }

    // Calculate the delta for the hidden and input layers
    for (RLayerIterator i = mNeurons.rbegin()+1; i != mNeurons.rend(); i++)
    {
        for (NeuronIterator j = (*i).begin(); j != (*i).end(); j++)
        {
            // Calculate delta sum for all connected neurons
            float sum = 0.f;
            //for (RLayerIterator k = i-1; k != mNeurons.rbegin(); k--)
            for (LayerIterator k = mNeurons.begin(); k != mNeurons.end(); k++)
                for (NeuronIterator l = (*k).begin(); l < (*k).end(); l++)
                    sum += (*l)->calculateDeltaSum((*j));

            // Calculate the delta
            float delta = (*j)->getOutput() * (1.f-(*j)->getOutput()) * sum;
            (*j)->setDelta(delta);
        }
    }

    // Finally, adjust the weights of the neurons
    for (LayerIterator i = mNeurons.begin(); i != mNeurons.end(); i++)
    {
        for (NeuronIterator j = (*i).begin(); j != (*i).end(); j++)
        {
            (*j)->adjustWeights(mLearningRate);
        }
    }

    // Propagate to input if need be
    if (mPropagateToInput)
    {
        // Iterate through neurons in input layer
        for (NeuronIterator it = mNeurons.front().begin(); it != mNeurons.front().end(); it++)
        {
            int index = std::distance(mNeurons.front().begin(), it);

            // For the inputs, the delta sum will be the input_neuron_delta*input, where the input is the "weight"
            float sum = (*it)->getDelta()*mLastInput[index];

            // Calculate the delta
            float delta = mLastInput[index] * (1.f - mLastInput[index]) * sum;

            // Adjust the input as it were a weight
            mLastInput[index] += mLearningRate * delta * mLastInput[index];
        }
    }
}

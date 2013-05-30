#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Neuron.h"
#include "InputNeuron.h"
#include "ActivationNeuron.h"
#include "ContextNeuron.h"
#include "BiasNeuron.h"
#include "NeuralNetwork.h"

#include <cmath>

int main()
{
    srand(time(NULL));

    std::cout << "Welcome to Neural Network Stuff!\n";
    std::cout << "Teddy DeRego 2013\n\n";

    NeuralNetwork network;
    network.setLearningRate(0.7f);
    //network.setPropagateToInput(true);

    network.createLayer<InputNeuron>(2);
    network.createLayer<BiasNeuron>(1);
    network.createLayer<ActivationNeuron>(10);
    network.createContextLayer(2);
    network.createLayer<BiasNeuron>(1);
    network.createLayer<ActivationNeuron>(1);

    network.connectLayerFully(0, 3);
    network.connectLayerFully(1, 3);
    network.connectLayerFully(3, 5);
    network.connectLayerFully(4, 5);

    network.randomizeWeights(-1.f, 1.f);

    float t_in[4][2] = {
    {0, 0.0},
    {0.1, 0.9},
    {0.9, 0.1},
    {0, 0.0}
    };

    float t_out[4][1] = {
    {0.0f},
    {0.3f},
    {0.6f},
    {1.f}
    };

    std::cout << "Desired Output Sequence:\n";
    for (int i = 0; i < 4; i++)
    {
        std::cout << t_out[i][0] << std::endl;
    }

    for (int epoch = 1; epoch <= 10000; epoch++)
    {
        for (int i = 0; i < 4; i++)
        {
            network.simulate(t_in[i]);
            network.backpropTrain(t_out[i]);
        }
    }

    std::cout << "Trained Output Sequence:\n";
    for (int i = 0; i < 4; i++)
    {
        float *out = network.simulate(t_in[i]);
        std::cout << out[0] << std::endl;
    }

    std::cout << "Inputs:\n";
    for (int i = 0; i < 4; i++)
        std::cout << t_in[i][0] << std::endl;

    return 0;
}

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cstddef>
#include <vector>

class Neuron;

/// \brief Implements a feed-forward neural network.
class NeuralNetwork
{
    public:
        NeuralNetwork();
        virtual ~NeuralNetwork();

        template <class T>
        void createLayer(int neuronCount)
        {
            std::vector <Neuron*> layer;
            for (int i = 0; i < neuronCount; i++)
                layer.push_back(new T);
            mNeurons.push_back(layer);
        }

        void createContextLayer(int baseLayer);

        void connectLayerFully(int sendLayer, int receiveLayer);

        /// \brief Randomizes all of the weights in the network.
        /// \param min Minimum value of randomization.
        /// \param max Maximum value of randomization.
        void randomizeWeights(float min, float max);

        /// \brief Simulates the network on a set of inputs
        /// \return Floating point output array with as many elements as the output layer of this
        /// network.
        float *simulate(float *inputs);

        /// \brief Train using error backpropagation.
        void backpropTrain(const float *trainOutput);

        /// \brief Add a new layer of neurons to the network.
        void addLayer(std::vector <Neuron*> layer){mNeurons.push_back(layer);}

        /// \brief Gets the learning rate for this network.
        /// \return The learning rate of this network
        float getLearningRate(){return mLearningRate;}

        /// \brief Gets whether or not this network propagates errors to the input layer.
        /// \return Boolean value of whether or not the network propagates errors to the input
        /// layer.
        bool getPropagateToInput(){return mPropagateToInput;}

        /// \brief Sets the learning rate of this network.
        /// \param learningRate New value for the learning rate.
        void setLearningRate(float learningRate){mLearningRate=learningRate;}

        /// \brief Sets whether or not to propagate errors to the input.
        /// \note Activating this will store a pointer to the supplied input, so the pointer needs to still be
        /// in the memory at the time of training.
        /// \param propagate True to activate propagation to inputs, false to deactivate.
        void setPropagateToInput(bool propagate){mPropagateToInput=propagate;}

    private:
        /// All of the neurons in this network. Each array of neurons in this array is a layer.
        std::vector <std::vector <Neuron*> > mNeurons;

        /// The learning rate of this network
        float mLearningRate;

        /// Setting this flag will tell the network to modify the input to better fit the output
        bool mPropagateToInput;

        /// Most recent input array.
        float *mLastInput;

        typedef std::vector<std::vector<Neuron*> >::iterator LayerIterator;
        typedef std::vector<std::vector<Neuron*> >::reverse_iterator RLayerIterator;
        typedef std::vector<Neuron*>::iterator NeuronIterator;
        typedef std::vector<Neuron*>::reverse_iterator RNeuronIterator;
};

#endif // NEURALNETWORK_H

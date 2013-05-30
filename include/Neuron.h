#ifndef NEURON_H
#define NEURON_H

#include <cstddef>
#include <vector>

class Neuron;

class Connection
{
    public:
        Connection()
        {
            mSender = NULL;
            mWeight = 1.f;
        }

        Connection(Neuron *sender, float weight = 1.f) :
        mSender(sender), mWeight(weight) {}

        void adjustWeight(float adjustment){mWeight+=adjustment;}

        // Accessors
        Neuron *getSender(){return mSender;}
        float getWeight(){return mWeight;}

        // Mutators
        void setSender(Neuron *sender){mSender=sender;}
        void setWeight(float weight){mWeight=weight;}

    private:
        Neuron *mSender; // The neuron sending the data
        float mWeight; // The weight of this connection: input to receiver = sender_output*weight
};

class Neuron
{
    public:
        Neuron();
        virtual ~Neuron();

        virtual void calculateInput(){};
        virtual float simulate(){return 0.f;}
        virtual void postSimulate(){}

        void addConnection(Connection connection){mConnections.push_back(connection);}

        /// Randomizes the weight on each connection
        void randomizeWeights(float min, float max);

        /// Sums the weights multiplied by the delta
        float calculateDeltaSum(Neuron *sender);

        /// Adjusts the weights based on the calculated delta and a supplied learning rate
        void adjustWeights(float learningRate);

        // Accessors
        float getInput(){return mInput;}
        float getDelta(){return mDelta;}
        float getOutput(){return mOutput;}

        // Mutators
        void setInput(float input){mInput=input;}
        void setDelta(float d){mDelta=d;}

    protected:
        float mInput;
        float mOutput;
        float mDelta;

        std::vector <Connection> mConnections; // Connections to this neuron
};

#endif // NEURON_H

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "Layer.h"
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

using namespace std;

namespace neural {
  /**
   * A back-propagation neural network.
   */
  class Network {
  public:
    /**
     * Construct a new Neural Network.
     * @param input the number of input neurons
     * @param output the number of output neurons
     * @param hidden an optional vector containing the number of neurons for each hidden layer
     */
    Network(int input, int output, vector<int> hidden = vector<int>());
    static Network read(string &filename);
    static Network read(istream &s);
    
    /**
     * Train the net with a single test case
     * @param learning_rate controls the speed of learning (see Neuron::updateWeights() )
     * @return the error for this case after back propagation
     */
    double trainSingle(vector<double> input, vector<double> expected_output, double learning_rate = 0.3);

    //! Run the neural network for the given input
    vector<double> run(vector<double> input);
    inline int Layers() const { return layerCount; };
    inline int Inputs() const { return inputLayer.size(); };
    inline int Outputs() const { return outputLayer->size(); };
    inline vector<double> Output() const { return outputLayer->Output(); };
    bool write(string &filename) const;
    bool write(ostream &s) const;
  private:
    Network(int input, shared_ptr<Layer> hidden, shared_ptr<Layer> output);
    int layerCount;
    //! Input layer just consists of data
    vector<double> inputLayer;
    // Layers in between are accessed via prev and next pointers
    shared_ptr<Layer> firstHidden;
    shared_ptr<Layer> outputLayer;
    double calculateError();
  };
}

#endif

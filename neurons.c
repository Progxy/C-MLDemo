// This file contains all the functions to generate and initialize the neural network, including all of its neurons

#include <stdio.h>
#include <stdlib.h>
#include "./neurons.h"
#include "./utils.h"

void init_nn(NeuralNetwork* neuralNetwork) {
    for (size_t i = 0; i < neuralNetwork -> layers; ++i) {
        for (size_t j = 0; j < neuralNetwork -> neurons_count[i]; ++j) {
            init_neuron(&((neuralNetwork -> neurons)[i][j]));
        }
    }

    return;
}

void init_neuron(Neuron* neuron) {
    // Init inputs
    for (size_t i = 0; i < neuron -> input_count; ++i) {
        (neuron -> inputs)[i] = rand_float();
    }

    // Init bias 
    neuron -> bias = rand_float();

    return;
}

NeuralNetwork generate_nn(size_t layers, size_t* neurons, size_t** inputs_count) {
    // Init the neural network
    NeuralNetwork neuralNetwork = {};
    neuralNetwork.neurons = calloc(layers, sizeof(Neuron*));
    neuralNetwork.layers = layers;
    neuralNetwork.neurons_count = neurons;

    for (size_t i = 0; i < layers; ++i) {
        // Init memory for the layer
        neuralNetwork.neurons[i] = calloc(neurons[i], sizeof(Neuron));
        for (size_t j = 0; j < neurons[i]; ++j) {
            // Add a neuron with the given inputs
            neuralNetwork.neurons[i][j] = generate_neuron(inputs_count[i][j]);
        }
    }

    return neuralNetwork;
}

Neuron generate_neuron(size_t input_count) {
    Neuron neuron = {
        0.f,
        NULL,
        input_count
    };

    return neuron;
}

// This file contains all the functions to generate and initialize the neural network, including all of its neurons

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./neurons.h"
#include "./layers.h"
#include "./utils.h"


NeuralNetwork alloc_nn(size_t* arch, size_t arch_count) {
    NeuralNetwork neuralNetwork = {
        .layers = malloc(sizeof(Layer) * (arch_count)),
        .arch_count = arch_count
    };
    
    // Input layer
    neuralNetwork.layers[0].activation = matrix_alloc(1, arch[0]);

    // Generate layers
    for (size_t i = 1; i < neuralNetwork.arch_count; ++i) {
        neuralNetwork.layers[i] = layer_alloc(arch[i - 1], arch[i]);
    }

    return neuralNetwork;
}

void print_nn(NeuralNetwork neuralNetwork, const char* name) {
    printf("%s:[\n", name);
    print_matrix(neuralNetwork.layers[0].activation, "a0");
    for (size_t i = 1; i < neuralNetwork.arch_count; ++i) {
        char name[256];
        snprintf(name, 256, "w%zu", i);
        print_matrix(neuralNetwork.layers[i].weight, name);
        snprintf(name, 256, "b%zu", i);
        print_matrix(neuralNetwork.layers[i].bias, name);
        snprintf(name, 256, "a%zu", i);
        print_matrix(neuralNetwork.layers[i].activation, name);
    }
    printf("\n]\n");

    return;
}

void forward_nn(NeuralNetwork neuralNetwork, Matrix input) {
    assert(neuralNetwork.layers[0].activation.cols == input.cols);

    // Pass the input to the activation of the input layer
    neuralNetwork.layers[0].activation.data = input.data;
    activate_matrix(neuralNetwork.layers[0].activation);

    for (size_t i = 1; i < neuralNetwork.arch_count; ++i) {
        dot_matrix(neuralNetwork.layers[i].activation, neuralNetwork.layers[i - 1].activation, neuralNetwork.layers[i].weight);
        sum_matrix(neuralNetwork.layers[i].activation, neuralNetwork.layers[i].bias);
        activate_matrix(neuralNetwork.layers[i].activation);
    }

    return;
}

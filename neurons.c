// This file contains all the functions to generate and initialize the neural network, including all of its neurons

#include <stdio.h>
#include <stdlib.h>
#include "./neurons.h"
#include "./layers.h"
#include "./utils.h"


NeuralNetwork nn_alloc(size_t* arch, size_t arch_count) {
    NeuralNetwork neuralNetwork = {
        .layers = malloc(sizeof(Layer) * (arch_count)),
        .arch_count = arch_count
    };
    
    // Input layer
    neuralNetwork.layers[0].activation = matrix_alloc(arch[0], 1);

    // Generate layers
    for (size_t i = 1; i < neuralNetwork.arch_count; ++i) {
        neuralNetwork.layers[i] = layer_alloc(arch[i], arch[i - 1]);
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
    printf("\n]");

    return;
}

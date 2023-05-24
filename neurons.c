// This file contains all the functions to generate and initialize the neural network, including all of its neurons

#include <stdio.h>
#include <stdlib.h>
#include "./neurons.h"
#include "./layers.h"
#include "./utils.h"

NeuralNetwork nn_alloc(Matrix input, Matrix output, size_t* arch, size_t arch_len) {
    NeuralNetwork neuralNetwork = {
        .layers = malloc(sizeof(Layer) * (arch_len - 2)),
        .input = input,
        .arch = arch,
        .output = output,
        .first_activation = matrix_alloc(input.rows, 1)
    };
    
    // Generate layers
    for (size_t i = 1; i < arch_len; ++i) {
        neuralNetwork.layers[i] = layer_alloc(arch[i + 1], arch[i]);
    }

    return neuralNetwork;
}
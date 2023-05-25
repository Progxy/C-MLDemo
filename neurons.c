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

void forward_nn(NeuralNetwork neuralNetwork) {
    for (size_t i = 1; i < neuralNetwork.arch_count; ++i) {
        dot_matrix(neuralNetwork.layers[i].activation, neuralNetwork.layers[i - 1].activation, neuralNetwork.layers[i].weight);
        sum_matrix(neuralNetwork.layers[i].activation, neuralNetwork.layers[i].bias);
        activate_matrix(neuralNetwork.layers[i].activation);
    }

    return;
}

void zero_nn(NeuralNetwork neuralNetwork) {
    fill_matrix(neuralNetwork.layers[0].activation, 0);
    for (size_t i = 1; i < neuralNetwork.arch_count; ++i) {
        fill_matrix(neuralNetwork.layers[i].activation, 0);
        fill_matrix(neuralNetwork.layers[i].weight, 0);
        fill_matrix(neuralNetwork.layers[i].bias, 0);
    }

    return;
}

void backprop_nn(NeuralNetwork neuralNetwork, NeuralNetwork gradient, Matrix input, Matrix output) {
    assert(INPUT_NN(neuralNetwork).cols == input.cols);
    assert(OUTPUT_NN(neuralNetwork).cols == output.cols);
    assert(input.rows == output.rows);

    size_t n = input.rows;

    zero_nn(gradient);

    for (size_t i = 0; i < n; ++i) {
        // Pass the input to the activation of the input layer
        copy_matrix(INPUT_NN(neuralNetwork), row_matrix(input, i));
        activate_matrix(INPUT_NN(neuralNetwork));
        forward_nn(neuralNetwork);

        // Clear the activation matrix for each layer
        for (size_t j = 0; j < neuralNetwork.arch_count; ++i) {
            fill_matrix(neuralNetwork.layers[j].activation, 0);
        }

        // Store the difference between the current output and the expected output into the output of the gradient to start the backpropagation
        for (size_t j = 0; j < output.cols; ++j) {
            MATRIX_AT(OUTPUT_NN(gradient), 0, j) = MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, j) - MATRIX_AT(output, i, j);
        }

        // Start calculating the gradient of the l-th layer based on the gradient of the next layer
        for (size_t l = neuralNetwork.arch_count - 1; l > 0; --l) {
            for (size_t c = 0; neuralNetwork.layers[l].activation.cols; ++c) {
                float activation = MATRIX_AT(neuralNetwork.layers[l].activation, 0, c);
                float diffActivation = MATRIX_AT(gradient.layers[l].activation, 0, c);
                // Calculate the differential for the bias based on the activation matrix of the next layer and it's differential
                MATRIX_AT(gradient.layers[l].bias, 0, c) = 2 * diffActivation * activation * (1 - activation);
                // Calculate the differential for the weights and the activation
                for (size_t r = 0; r < neuralNetwork.layers[l - 1].activation.cols; ++r) {
                    float previousActivation = MATRIX_AT(neuralNetwork.layers[l-1].activation, 0, r);
                    float weight = MATRIX_AT(neuralNetwork.layers[l].weight, r, c);
                    MATRIX_AT(gradient.layers[l].weight, r, c) += 2 * diffActivation * activation * (1 - activation) * previousActivation;
                    MATRIX_AT(gradient.layers[l - 1].activation, 0, r) += 2 * diffActivation * activation * (1 - activation) * weight;
                }
            }
        }

        // Get the average for each gradient
        for (size_t l = 1; l < gradient.arch_count; ++l) {
            // 1/n * gradient for each weight
            for (size_t r = 0; r < gradient.layers[l].weight.rows; ++r) {
                for (size_t c = 0; c < gradient.layers[l].weight.cols; ++c) {
                    MATRIX_AT(gradient.layers[l].weight, r, c) /= n;
                }
            }

            // 1/n * gradient for each bias
            for (size_t c = 0; c < gradient.layers[l].bias.cols; ++c) {
                MATRIX_AT(gradient.layers[l].bias, 0, c) /= n;
            }
        }
    }

    return;
}

void learn_nn(NeuralNetwork neuralNetwork, NeuralNetwork gradient, float rate) {
    // Update the current value of the weights by subtracting the gradient multiplied by the learning rate
    for (size_t l = 1; l < neuralNetwork.arch_count; ++l) {
        for (size_t r = 0; r < neuralNetwork.layers[l].weight.rows; ++r) {
            for (size_t c = 0; c < neuralNetwork.layers[l].weight.cols; ++c) {
                MATRIX_AT(neuralNetwork.layers[l].weight, r, c) -= rate * MATRIX_AT(gradient.layers[l].weight, r, c);
            }
        }
    }

    // Update the current value of the bias by subtracting the gradient multiplied by the learning rate
    for (size_t l = 1; l < neuralNetwork.arch_count; ++l) {
        for (size_t c = 0; c < neuralNetwork.layers[l].bias.cols; ++c) {
            MATRIX_AT(neuralNetwork.layers[l].bias, 0, c) -= rate * MATRIX_AT(gradient.layers[l].bias, 0, c);
        }
    }

    return;

}

float cost_nn(NeuralNetwork neuralNetwork, Matrix input, Matrix output) {
    assert(INPUT_NN(neuralNetwork).cols == input.cols);
    assert(OUTPUT_NN(neuralNetwork).cols == output.cols);
    assert(input.rows == output.rows);

    float cost = 0;
    for (size_t i = 0; i < input.rows; ++i) {
        Matrix input_row = row_matrix(input, i);
        Matrix output_row = row_matrix(output, i);

        // Feed the network
        copy_matrix(INPUT_NN(neuralNetwork), input_row);
        activate_matrix(INPUT_NN(neuralNetwork));
        forward_nn(neuralNetwork);

        // Calculate the error and amplify it by multipling it by itself
        for (size_t j = 0; j < output.cols; ++j) {
            float difference = MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, j) - MATRIX_AT(output_row, 0, j);
            cost += difference * difference;
        }
    }

    return cost / input.rows;
}


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
        activate_matrix(neuralNetwork.layers[i].activation, neuralNetwork.layers[i].alpha);
    }

    return;
}

void calc_weighted_sum(NeuralNetwork neuralNetwork, size_t layer, Matrix matrix) {
    dot_matrix(matrix, neuralNetwork.layers[layer - 1].activation, neuralNetwork.layers[layer].weight);
    sum_matrix(matrix, neuralNetwork.layers[layer].bias);
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

void backprop_nn(NeuralNetwork neuralNetwork, NeuralNetwork gradient, Matrix input, Matrix output, float learning_rate) {
    assert(INPUT_NN(neuralNetwork).cols == input.cols);
    assert(OUTPUT_NN(neuralNetwork).cols == output.cols);
    assert(input.rows == output.rows);

    size_t n = input.rows;

    zero_nn(gradient);

    for (size_t i = 0; i < n; ++i) {
        // Pass the input to the activation of the input layer
        copy_matrix(INPUT_NN(neuralNetwork), row_matrix(input, i));
        forward_nn(neuralNetwork);

        // Clear the activation matrix for each layer
        for (size_t j = 0; j < gradient.arch_count; ++j) {
            fill_matrix(gradient.layers[j].activation, 0);
        }

        // Compute the gradient of the loss with respect to the activation of the output layer
        for (size_t j = 0; j < output.cols; ++j) {
            MATRIX_AT(OUTPUT_NN(gradient), 0, j) = MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, j) - MATRIX_AT(output, i, j);
        }

        // Start calculating the gradient of the l-th layer based on the gradient of the next layer
        for (int l = neuralNetwork.arch_count - 1; l > 0; --l) {
            Matrix weighted_sum = matrix_alloc(1, neuralNetwork.layers[l].activation.cols);
            for (size_t c = 0; c < neuralNetwork.layers[l].activation.cols; ++c) {
                float prevActivation = MATRIX_AT(neuralNetwork.layers[l-1].activation, 0, c);
                float diffActivation = MATRIX_AT(gradient.layers[l].activation, 0, c);
                float currentAlpha = MATRIX_AT(neuralNetwork.layers[l].alpha, 0, c);
                float z = MATRIX_AT(weighted_sum, 0, c);

                // Compute the gradient of the loss with respect to the weighted sum (z^l):
                // dz^l = dL/da^l * dprelu(z^l, alpha^l)/dz^l, where the second term is equal to (if (z^l >= 0) -> 1 else -> alpha)
                float diffZ = diffActivation * (z >= 0 ? 1 : currentAlpha);                

                // Calculate the differential for the bias based on the activation matrix of the next layer and it's differential
                MATRIX_AT(gradient.layers[l].bias, 0, c) = diffZ;      
                
                // Compute the gradient of the loss with respect to alpha:
                // dL/dalpha^l = dz^l * (a^(l-1) - alpha^l * sign(z^l)) # Here, sign(z^l) is the sign function of z^l.
                MATRIX_AT(gradient.layers[l].alpha, 0, c) = diffZ * (prevActivation - currentAlpha * signf(z));
                
                // Calculate the differential for the weights and the activation
                for (size_t r = 0; r < neuralNetwork.layers[l - 1].activation.cols; ++r) {
                    float previousActivation = MATRIX_AT(neuralNetwork.layers[l-1].activation, 0, r);
                    //float weight = MATRIX_AT(neuralNetwork.layers[l].weight, r, c);
                    MATRIX_AT(gradient.layers[l].weight, r, c) = diffZ * previousActivation;
                    //MATRIX_AT(gradient.layers[l - 1].activation, 0, r) = diffZ * weight;
                }
            }
            matrix_dealloc(weighted_sum);
        }

        learn_nn(neuralNetwork, gradient, learning_rate);
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
    
    // Update the current value of the alpha by subtracting the gradient multiplied by the learning rate
    for (size_t l = 1; l < neuralNetwork.arch_count; ++l) {
        for (size_t c = 0; c < neuralNetwork.layers[l].bias.cols; ++c) {
            MATRIX_AT(neuralNetwork.layers[l].bias, 0, c) -= rate * MATRIX_AT(gradient.layers[l].alpha, 0, c);
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
        forward_nn(neuralNetwork);

        // Calculate the loss
        // (1/2) * (a^L - y)^2
        for (size_t j = 0; j < output.cols; ++j) {
            float half = (float) 1 / (float) 2;
            cost += half * powerf(2, MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, j) - MATRIX_AT(output_row, 0, j));
        }
    }
    
    // Return the average cost
    return cost / input.rows;
}


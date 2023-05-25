#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./neurons.h"

int main() {
    init_seed();
    size_t arch[] = {2, 2, 1};
    
    float input_data[] = {
            0, 0,
            0, 1,
            1, 0, 
            1, 1
    };
    
    Matrix input = (Matrix) {
        .cols = 2,
        .rows = 4,
        .data = input_data
    };    
    
    float output_data[] = {
            0,
            1,
            1,
            0
    };

    Matrix output = (Matrix) {
        .cols = 1,
        .rows = 4,
        .data = output_data
    };

    NeuralNetwork neuralNetwork = alloc_nn(arch, ARRAY_LEN(arch));
    NeuralNetwork gradient = alloc_nn(arch, ARRAY_LEN(arch));

    for (size_t i = 0; i < 100; ++i) {
        backprop_nn(neuralNetwork, gradient, input, output);
        learn_nn(neuralNetwork, gradient, 1);
        printf("%zu: cost = %f\n", i, cost_nn(neuralNetwork, input, output));
    }

    PRINT_NN(neuralNetwork);

    for (size_t i = 0; i < 4; ++i) {
        copy_matrix(INPUT_NN(neuralNetwork), row_matrix(INPUT_NN(neuralNetwork), i));
        forward_nn(neuralNetwork);
        printf("%f ^ %f = %f\n", MATRIX_AT(input, i, 0), MATRIX_AT(input, i, 1), MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, 0));
    }

    return 0;
}

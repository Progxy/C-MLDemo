#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./neurons.h"

int main() {
    init_seed();
    // size_t arch[] = {2, 2, 1};
    
    float data[] = {
            0, 0, 0,
            0, 1, 1,
            1, 0, 1,
            1, 1, 0
    };
    
    Matrix tr_input = (Matrix) {
        .cols = 3,
        .rows = 4,
        .data = data
    };    

    Matrix input = row_matrix(tr_input, 1);

    // NeuralNetwork neuralNetwork = alloc_nn(arch, ARRAY_LEN(arch));
    // NeuralNetwork gradient = alloc_nn(arch, ARRAY_LEN(arch));
    // float rate = 1e-1;

    // for (size_t i = 0; i < 10000; ++i) {
    //     backprop_nn(neuralNetwork, gradient, input, output, rate);
    //     printf("%zu: cost = %f\n", i, cost_nn(neuralNetwork, input, output));
    // }

    // PRINT_NN(neuralNetwork);

    // for (size_t i = 0; i < 4; ++i) {
    //     copy_matrix(INPUT_NN(neuralNetwork), row_matrix(input, i));
    //     forward_nn(neuralNetwork);
    //     printf("%f ^ %f = %f\n", MATRIX_AT(input, i, 0), MATRIX_AT(input, i, 1), MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, 0));
    // }

    return 0;
}

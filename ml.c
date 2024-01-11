#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./neurons.h"
#include "./matrix.h"
#include "./datasets_reader.h"

int main() {
    init_seed();
    
    size_t arch[] = {9, 8, 10, 10, 8, 4, 1};
    
    Matrix tr_input = read_dataset("./Datasets/tic_tac_toe_ds.arff");

    Matrix input = sub_matrix(tr_input, tr_input.rows, 9, 0, 0);
    Matrix output = sub_matrix(tr_input, tr_input.rows, 1, 0, 9);

    NeuralNetwork neuralNetwork = alloc_nn(arch, ARRAY_LEN(arch));
    NeuralNetwork gradient = alloc_nn(arch, ARRAY_LEN(arch));
    float rate = 1e-6;

    for (size_t i = 0; i < 5000; ++i) {
        backprop_nn(neuralNetwork, gradient, input, output, rate);
        printf("%zu: cost = %f\n", i, cost_nn(neuralNetwork, input, output));
    }

    PRINT_NN(neuralNetwork);

    for (size_t i = 0; i < 1; ++i) {
        copy_matrix(INPUT_NN(neuralNetwork), row_matrix(input, i));
        forward_nn(neuralNetwork);
        for (size_t j = 0; j < input.cols; ++j) {
            printf("%f, ", MATRIX_AT(input, i, j));
        }
        printf(" = %f\n", MATRIX_AT(OUTPUT_NN(neuralNetwork), 0, 0));
    }

    return 0;
}

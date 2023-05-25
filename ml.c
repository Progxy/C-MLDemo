#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./neurons.h"

int main() {
    init_seed();
    size_t arch[] = {4, 3, 2};
    NeuralNetwork neuralNetwork = alloc_nn(arch, ARRAY_LEN(arch));
    PRINT_NN(neuralNetwork);
    Matrix input = matrix_alloc(1, 4);
    rand_matrix(input, 0, 1);
    return 0;
}

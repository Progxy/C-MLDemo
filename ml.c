#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./neurons.h"

int main() {
    init_seed();
    size_t arch[] = {4, 3, 2, 1};
    NeuralNetwork neuralNetwork = nn_alloc(arch, ARRAY_LEN(arch));
    PRINT_NN(neuralNetwork);
    return 0;
}

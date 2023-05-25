#include <stdio.h>
#include <stdlib.h>
#include "./layers.h"
#include "./utils.h"

Layer layer_alloc(size_t rows, size_t cols) {
    Layer layer;

    layer.activation = matrix_alloc(1, cols);
    fill_matrix(layer.activation, 0);
    layer.bias = matrix_alloc(1, cols);
    fill_matrix(layer.bias, 0);
    layer.weight = matrix_alloc(rows, cols);
    rand_matrix(layer.weight, 0, 1);
    
    return layer;
}

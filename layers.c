#include <stdio.h>
#include <stdlib.h>
#include "./layers.h"
#include "./utils.h"

Layer layer_alloc(size_t rows, size_t cols) {
    Layer layer;

    layer.activation = matrix_alloc(cols, 1);
    fill_matrix(layer.activation, 0);
    layer.bias = matrix_alloc(cols, 1);
    fill_matrix(layer.bias, 0);
    layer.weight = matrix_alloc(rows, cols);

    return layer;
}

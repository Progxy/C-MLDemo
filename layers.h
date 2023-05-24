#ifndef _LAYERS_H_
#define _LAYERS_H_

#include "./matrix.h"

typedef struct {
    Matrix weight;
    Matrix bias;
    Matrix activation;
} Layer;

Layer layer_alloc(size_t rows, size_t cols);

#endif //_LAYERS_H_
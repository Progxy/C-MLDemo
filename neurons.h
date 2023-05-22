#ifndef _NEURONS_H_
#define _NEURONS_H_

#include <stdlib.h>
#include "./matrix.h"

typedef struct {
    Matrix weight;
    Matrix bias;
    Matrix activation;
} Layer;

typedef struct {
    Matrix input;
    Layer* layers;
    size_t* arch;
} NeuralNetwork;

NeuralNetwork nn_alloc(Matrix input, size_t* arch);

#endif //_NEURONS_H_
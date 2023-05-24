#ifndef _NEURONS_H_
#define _NEURONS_H_

#include "./matrix.h"
#include "./layers.h"

typedef struct {
    Matrix input;
    Layer* layers;
    size_t* arch;
    Matrix first_activation;
    Matrix output;
} NeuralNetwork;

NeuralNetwork nn_alloc(Matrix input, Matrix output, size_t* arch, size_t arch_len);

#endif //_NEURONS_H_
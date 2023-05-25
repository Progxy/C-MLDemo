#ifndef _NEURONS_H_
#define _NEURONS_H_

#include "./matrix.h"
#include "./layers.h"

#define PRINT_NN(nn) print_nn(nn, #nn)

typedef struct {
    Layer* layers;
    size_t arch_count;
} NeuralNetwork;

NeuralNetwork nn_alloc(size_t* arch, size_t arch_count);
void print_nn(NeuralNetwork neuralNetwork, const char* name);

#endif //_NEURONS_H_
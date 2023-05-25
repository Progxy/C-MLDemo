#ifndef _NEURONS_H_
#define _NEURONS_H_

#include "./matrix.h"
#include "./layers.h"

#define PRINT_NN(nn) print_nn(nn, #nn)

typedef struct {
    Layer* layers;
    size_t arch_count;
} NeuralNetwork;

NeuralNetwork alloc_nn(size_t* arch, size_t arch_count);
void print_nn(NeuralNetwork neuralNetwork, const char* name);
void forward_nn(NeuralNetwork neuralNetwork, Matrix input);

#endif //_NEURONS_H_
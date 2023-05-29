#ifndef _NEURONS_H_
#define _NEURONS_H_

#include "./matrix.h"
#include "./layers.h"

#define PRINT_NN(nn) print_nn(nn, #nn)
#define INPUT_NN(nn) (nn).layers[0].activation
#define OUTPUT_NN(nn) (nn).layers[(nn).arch_count - 1].activation

typedef struct {
    Layer* layers;
    size_t arch_count;
    float alpha;
} NeuralNetwork;

NeuralNetwork alloc_nn(size_t* arch, size_t arch_count);
void print_nn(NeuralNetwork neuralNetwork, const char* name);
void forward_nn(NeuralNetwork neuralNetwork);
void backprop_nn(NeuralNetwork neuralNetwork, NeuralNetwork gradient, Matrix input, Matrix output, float learning_rate);
void zero_nn(NeuralNetwork neuralNetwork);
void learn_nn(NeuralNetwork neuralNetwork, NeuralNetwork gradient, float rate);
float cost_nn(NeuralNetwork neuralNetwork, Matrix input, Matrix output);

#endif //_NEURONS_H_
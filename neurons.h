#pragma once

#ifndef _NEURONS_H_
#define _NEURONS_H_

#include <stdlib.h>

typedef struct Neuron {
    float bias;
    float* inputs;
    size_t input_count;
} Neuron;

typedef struct NeuralNetwork {
    Neuron** neurons;
    size_t layers;
    size_t* neurons_count;
} NeuralNetwork; 

void init_nn(NeuralNetwork* neuralNetwork);
void init_neuron(Neuron* neuron);
NeuralNetwork generate_nn(size_t layers, size_t* neurons, size_t** inputs_count);
Neuron generate_neuron(size_t input_count);

#endif
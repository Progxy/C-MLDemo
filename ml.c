#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRAINING_INPUT_LENGTH 10
#define LEARNING_RATE 1e-3
#define EPSILON 1e-3

typedef struct Neuron{
    float w1;
    float bias;
} Neuron;

float train_data[][2] = {
    {0, 0}, 
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8}, 
    {5, 10}, 
    {6, 12}, 
    {7, 14},
    {8, 16}, 
    {9, 18}
};

float cost(Neuron neuron) {
    float result = 0.f;

    for (size_t i = 0; i < TRAINING_INPUT_LENGTH; ++i) {
        // Calculate the size of the error 
        float errorSize = (neuron.w1 * train_data[i][0] + neuron.bias) - train_data[i][1];
        // Amplify the size of the error
        result += errorSize * errorSize;
    }

    return result;
}

float randf() {
    return (float) rand() / (float) RAND_MAX;
}

void train(size_t train_size, Neuron* neuron) {
    Neuron tempNeuron = {0.f, 0.f};

    for (size_t i = 0; i < train_size; ++i) {
        float actualCost = cost(*neuron);
        tempNeuron.w1 = neuron -> w1 + EPSILON;
        tempNeuron.bias = neuron -> bias;
        float dw = (cost(tempNeuron) - actualCost) / EPSILON;
        tempNeuron.w1 = neuron -> w1;
        tempNeuron.bias = neuron -> bias + EPSILON;
        float db = (cost(tempNeuron) - actualCost)/EPSILON;
        neuron -> w1 -= LEARNING_RATE * dw;
        neuron -> bias -= LEARNING_RATE * db;
    }

    return;
}

int main() {
    // Initialize the seed
    srand(time(0));
    Neuron neuron = {randf(), randf()};
    printf("Initial neuron configuration: w1: %f, bias: %f\n", neuron.w1, neuron.bias);
    
    train(100000000, &neuron); 

    // Show training result
    printf("Result:\nw1: %f, bias: %f, loss/cost: %f\n", neuron.w1, neuron.bias, cost(neuron));
    
    for (size_t i = 0; i < TRAINING_INPUT_LENGTH; ++i) {
        printf("calculated: %f, expected: %f\n", (neuron.w1 * train_data[i][0] + neuron.bias), train_data[i][1]);
    }

    return 0;
}
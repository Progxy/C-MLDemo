// This file contains collects all the utility functions used in other files

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init_seed() {
    return srand(time(0));
}

float rand_float() {
    return (float) rand() / (float) RAND_MAX; 
}

float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}

float preluf(float x, float alpha) {
    return x >= 0 ? x : alpha * x;
}

float powerf(size_t base, float val) {
    if (base == 0) {
        return 1.f;
    } 

    float result = val;

    for (size_t i = 1; i < base; ++i) {
        result *= val;
    }

    return result;
}

float signf(float val) {
    return val == 0.f ? 0.f : val > 0.f ? 1.f : -1.f;
}
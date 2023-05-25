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

float absf(float x) {
    return x >= 0 ? x : -x;
}

float reluf(float x) {
    return (x + absf(x)) / 2;
}

float preluf(float x, float alpha) {
    return x >= 0 ? x : (alpha * x);
}

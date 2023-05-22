// This file contains collects all the utility functions used in other files

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_seed() {
    return srand(time(0));
}

float rand_float() {
    return (float) rand() / (float) RAND_MAX; 
}

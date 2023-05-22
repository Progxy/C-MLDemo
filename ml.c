#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./matrix.h"

int main() {
    init_seed();
    Matrix matrix = matrix_alloc(2, 2);
    rand_matrix(matrix, 2, 5);
    PRINT_MATRIX(matrix);
    return 0;
}
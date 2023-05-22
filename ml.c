#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"
#include "./matrix.h"

int main() {
    init_seed();
    Matrix matrix = matrix_alloc(2, 2);
    fill_matrix(matrix, 2);
    Matrix id_matrix = gen_id_matrix(2);
    Matrix result_matrix = matrix_alloc(2,2);
    dot_matrix(result_matrix, matrix, id_matrix);
    PRINT_MATRIX(result_matrix);
    return 0;
}
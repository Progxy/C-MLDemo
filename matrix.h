#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdlib.h>

#define MATRIX_AT(matrix, row, col) (matrix).data[(matrix).cols * (row) + (col)]
#define PRINT_MATRIX(matrix) print_matrix(matrix, #matrix)

typedef struct {
    size_t rows;
    size_t cols;
    float* data;
} Matrix;

Matrix matrix_alloc(size_t rows, size_t cols);
void rand_matrix(Matrix matrix, float min, float max);
void fill_matrix(Matrix matrix, float value);
void sum_matrix(Matrix a, Matrix b);
void dot_matrix(Matrix dest, Matrix a, Matrix b);
void print_matrix(Matrix matrix, const char* name);
Matrix gen_id_matrix(size_t size);

#endif
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
void activate_matrix(Matrix matrix, Matrix alpha);
void copy_matrix(Matrix dest, Matrix src);
Matrix row_matrix(Matrix matrix, size_t row);
void matrix_dealloc(Matrix matrix);
void reshape_matrix(Matrix* mat, size_t rows, size_t cols, float* new_data);
void shuffle_matrix(Matrix matrix);
Matrix sub_matrix(Matrix matrix, size_t rows, size_t cols, size_t row_start, size_t col_start);

#endif //_MATRIX_H_
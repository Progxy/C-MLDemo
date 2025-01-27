// This file contains all the functions necessary to work with matrices

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./matrix.h"
#include "./utils.h"

Matrix matrix_alloc(size_t rows, size_t cols) {
    assert(rows > 0);
    assert(cols > 0);

    Matrix matrix = {
        .rows = rows,
        .cols = cols,    
        .data = malloc(sizeof(float) * rows * cols)
    };

    assert(matrix.data != NULL);

    return matrix;
}

void matrix_dealloc(Matrix matrix) {
    free(matrix.data);
    return;
}

void rand_matrix(Matrix matrix, float min, float max) {
    assert(min <= max);

    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            MATRIX_AT(matrix, i, j) = (rand_float() * (max - min)) + min;
        }
    }

    return;
}

void fill_matrix(Matrix matrix, float value) {
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            MATRIX_AT(matrix, i, j) = value;
        }
    }
    return;
}

void sum_matrix(Matrix a, Matrix b) {
    assert(a.cols == b.cols);
    assert(a.rows == b.rows);

    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            MATRIX_AT(a, i, j) += MATRIX_AT(b, i, j);
        }
    }

    return;
}

void dot_matrix(Matrix dest, Matrix a, Matrix b) {
    assert(a.cols == b.rows);
    assert(dest.rows == a.rows);
    assert(dest.cols == b.cols);

    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < b.cols; ++j) {
            MATRIX_AT(dest, i, j) = 0;
            for (size_t q = 0; q < a.cols; ++q) {
                MATRIX_AT(dest, i, j) += MATRIX_AT(a, i, q) * MATRIX_AT(b, q, j);
            }
        }
    }

    return;
}

void print_matrix(Matrix matrix, const char* name) {
    printf("%s = [\n", name);
    for (size_t i = 0; i < matrix.rows; ++i) {
        printf("\t");
        for (size_t j = 0; j < matrix.cols; ++j) {
            printf("%f, ", MATRIX_AT(matrix, i, j));
        }
        printf("\n");
    }
    
    printf("]\n");

    return;
}

Matrix gen_id_matrix(size_t size) {
    Matrix matrix = matrix_alloc(size, size);
    fill_matrix(matrix, 0);
    
    for (size_t i = 0; i < size; ++i) {
        MATRIX_AT(matrix, i, i) = 1;
    }

    return matrix;
}

void activate_matrix(Matrix matrix, Matrix alpha) {
    assert(matrix.rows == alpha.rows);
    
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            MATRIX_AT(matrix, i, j) = preluf(MATRIX_AT(matrix, i, j), MATRIX_AT(alpha, i, j));
        }
    }

    return;
}

void reshape_matrix(Matrix* mat, size_t rows, size_t cols, float* new_data) {
    mat -> rows = rows; 
    mat -> cols = cols; 
    if (new_data != NULL) {
        free(mat -> data);
        mat -> data = new_data;
        return;
    }
    mat -> data = (float*) realloc(mat -> data, rows * cols * sizeof(float));
    return;
} 

void copy_matrix(Matrix dest, Matrix src) {
    assert(dest.cols == src.cols);
    assert(dest.rows == src.rows);
    
    for (size_t i = 0; i < src.rows; ++i) {
        for (size_t j = 0; j < src.cols; ++j) {
            MATRIX_AT(dest, i, j) = MATRIX_AT(src, i, j);
        }
    }

    return;
}

Matrix row_matrix(Matrix matrix, size_t row) {
    return (Matrix) {
        .rows = 1,
        .cols = matrix.cols,
        .data = &MATRIX_AT(matrix, row, 0)
    };
}

Matrix sub_matrix(Matrix matrix, size_t rows, size_t cols, size_t row_start, size_t col_start) {
    float* data = malloc(rows * cols * sizeof(float));

    // Trim the matrix into the requested sub-matrix
    for (size_t r = row_start; r < (rows + row_start); ++r) {
        for (size_t c = col_start; c < (col_start + cols); ++c) {
            size_t new_row = r - row_start;
            size_t new_col = c - col_start;
            data[new_row * cols + new_col] = MATRIX_AT(matrix, r, c);
        }
    }

    return (Matrix) {
        .rows = rows,
        .cols = cols,
        .data = data
    };
}

void shuffle_matrix(Matrix matrix) {
    size_t max = matrix.rows * matrix.cols - 2;
    for (size_t i = 0; i < max; ++i) {
        size_t j = rand_int(i, max);
        float swap = matrix.data[i];
        matrix.data[i] = matrix.data[j];
        matrix.data[j] = swap;
    }

    return;
}

float froebinius_inn_prod(Matrix a, Matrix b) {
    assert(a.rows == b.rows && a.cols == b.cols);
    float sum = 0.0f;
    for (size_t i = 0; i < a.cols * a.rows; ++i) {
        sum += a.data[i] + b.data[i];
    }
    return sum;
}

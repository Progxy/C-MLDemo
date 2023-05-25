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

void activate_matrix(Matrix matrix) {
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            MATRIX_AT(matrix, i, j) = sigmoidf(MATRIX_AT(matrix, i, j));
        }
    }

    return;
}

#include <stdio.h>
#include <stdlib.h>
#include "./datasets_reader.h"
#include "./matrix.h"

static char* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    
    if (file == NULL) {
        printf("DATASETS_READER::READ_FILE: Error while opening the file!\n");
        return NULL;
    }

    // Get the length of the file
    fseek(file, 0, SEEK_END); // Go to the end of the file
    size_t length = ftell(file); // Get the position in bytes from the start
    fseek(file, 0, SEEK_SET); // Go back to the start

    char* data = calloc(length, sizeof(char));

    // Read the data
    if (length != fread(data, 1, length, file)) {
        free(data);
        printf("DATASETS_READER::READ_FILE: Size mismatch between data read size and file length!\n");
        return NULL;
    }

    if (ferror(file)) {
        free(data);
        printf("DATASETS_READER::READ_FILE: an error occured while reading the file!\n");
        return NULL;
    }

    fclose(file);

    return data;
}

Matrix read_dataset(const char* file_path) {
    Matrix dataset = matrix_alloc(1, 1);

    char* file_data = read_file(file_path);
    if (file_data == NULL) {
        matrix_dealloc(dataset);
        return (Matrix) {.rows = 0, .cols = 0, .data = NULL};
    }

    char** lines = (char**) calloc(1, sizeof(char*));
    size_t lines_count = 0;
    size_t line_count = 0;
    char* line = (char*) calloc(1, sizeof(char));
    for (size_t i = 0; file_data[i] != '\0'; ++i) {
        if (file_data[i] == '\n') {
            lines[lines_count] = line;
            lines_count++;
            lines = (char**) realloc(lines, sizeof(char*) * (lines_count + 1));
            line = calloc(1, sizeof(char));
            line_count = 0;
            continue;
        }

        line[line_count] = file_data[i];
        line_count++;
        line = (char*) realloc(line, sizeof(char) * (line_count + 1));
    }

    free(file_data);

    float* data = (float*) calloc(lines_count * 10, sizeof(float));
    size_t data_count = 0;

    printf("DEBUG_INFO: Lines content: \n\n");
    for (size_t i = 0; i < lines_count; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            char elem = lines[i][j * 2];
            data[data_count] = (elem == 'x' || elem == 'p') ? 1.0f : 0.0f;
            data_count++;
        }
        free(lines[i]);
    }

    free(lines);

    reshape_matrix(&dataset, lines_count, 10, data);

    return dataset;
}

#include "Matrix.hpp"
#include <stdio_ext.h>
#include <stdlib.h>

Matrix::Matrix(char* maze) {
    FILE *file = fopen(maze, "r");

    fscanf(file, "%d\n", &rows);
    fscanf(file, "%d\n", &columns);
    matrix = (int**)malloc(sizeof(int*) * rows);

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * columns);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("vai ficar louco\n");
            fscanf(file, "%d\n", &matrix[i][j]);
            // matrix[i][j] = fgetc(file);
            putchar('\n');
        }
        fscanf(file, "\n");
    }

    fclose(file);
}

Matrix::~Matrix() {
    printf("Destruindo Matrix \n");
    for (int i = 0; i < rows; i ++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** Matrix::getMatrix() {
    return matrix;
}

int Matrix::getColumns() {
    return columns;
}

int Matrix::getRows() {
    return rows;    
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%6d", matrix[i][j]);
        }
        putchar('\n');
    }
}
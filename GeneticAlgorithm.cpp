#include "GeneticAlgorithm.hpp"
#include <stdlib.h>
#include <stdio_ext.h>
#include <time.h>

GeneticAlgorithm::GeneticAlgorithm(Matrix *matrix) {
    costMatrix = matrix;
    pathsCount = matrix->getRows();
    pathsLength = matrix->getColumns();
    srand(time(NULL));
    paths = (int **)malloc(sizeof(int *) * pathsCount);
    for (int i = 0; i < pathsLength; i++) {
        paths[i] = (int *)malloc(sizeof(int) * pathsLength);
    }
    for(int i = 0; i < pathsLength; i++) {
        paths[0][i] = i;
    }
    for(int i = 1; i < pathsLength; i++) {
        for(int j = 0; j < pathsCount; j++) {
            paths[i][j] = rand() % paths[0][pathsLength - 1];
        }
    }
}

GeneticAlgorithm::~GeneticAlgorithm() {
    for(int i = 0; i < pathsCount; i++) {
        free(paths[i]);
    }
    free(paths);

    printf("Caminhos destruidos\n");
}

void GeneticAlgorithm::printPaths() {
    for(int i = 0; i < pathsCount; i++) {
        printf("Caminho %d: ", i);
        for (int j = 0; j< pathsLength; j++) {
            printf("%d, ", paths[i][j]);
        }
        putchar('\n');
    }
    // printf("Caminho 0: ");
    // for(int i = 0; i < pathsLength; i++) {
    //     printf("%d, ", paths[14][i]);
    // }
}
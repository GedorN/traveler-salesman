#include "GeneticAlgorithm.hpp"
#include <stdlib.h>
#include <stdio_ext.h>
#include <time.h>
#define BALANCE 20

GeneticAlgorithm::GeneticAlgorithm(Matrix *matrix) {
    costMatrix = matrix;
    pathsCount = matrix->getRows();
    pathsLength = matrix->getColumns();
    srand(time(NULL));
    paths = (int **)malloc(sizeof(int *) * pathsCount);
    costs = (int *)malloc(sizeof(int) * pathsCount);
    for (int i = 0; i < pathsLength; i++) {
        paths[i] = (int *)malloc(sizeof(int) * pathsLength);
    }
    int cost = 0;
    printf("\nSomando: ");


    //setting first path
    paths[0][0] = initIndex;
    for(int i = 0; i < pathsLength; i++) {
        if (i == initIndex) {
            paths[0][i+1] = i + 1;
            if (i != 0) {
                int aux = paths[0][i + 1];
                cost += matrix->getMatrix()[0][aux];
                printf("%d + ", matrix->getMatrix()[0][aux]);
            }
        } else {
            paths[0][i+1] = i;
            if (i != 0) {
                int aux = paths[0][i];
                cost += matrix->getMatrix()[0][aux];
                printf("%d + ", matrix->getMatrix()[0][aux]);
            }
        }
    }
    putchar('\n');
    cost += matrix->getMatrix()[pathsLength - 1][0];
    costs[0] = cost;

    // setting other paths
    for(int i = 1; i < pathsCount; i++) {
        paths[i][0] = initIndex;
        cost = 0;
        for(int j = 0; j < pathsLength; j++) {
            if (j == initIndex) {
                paths[i][j + 1] = rand() % paths[0][pathsLength - 1];
                if (j != 0) {
                    int aux = paths[i][j + 1];
                    cost+= matrix->getMatrix()[i][aux];
                }
                cost += matrix->getMatrix()[pathsLength - 1][i];
                costs[i] = cost;
            } else {
                paths[i][j + 1] = rand() % paths[0][pathsLength - 1];
                if (j != 0) {
                    int aux = paths[i][j + 1];
                    cost+= matrix->getMatrix()[i][aux];
                }
                cost += matrix->getMatrix()[pathsLength - 1][i];
                costs[i] = cost;
            }
        }
    }
    printPaths();

    crossover();
}

GeneticAlgorithm::~GeneticAlgorithm() {
    printf("\n\nMelhor caminho: ");
    for(int i = 0; i < pathsCount; i++) {
        printf("%d, ", lowerPath[i]);
    }
    putchar('\n');
    printf("Custo: %d", bestCost);
    for(int i = 0; i < pathsCount; i++) {
        free(paths[i]);
    }
    free(paths);

}

void GeneticAlgorithm::crossover() {
    int lowerCost = costs[0];
    int roulletSize = 0;
    int *roullet;
    int **newPopulation;
    int roulletCounter[pathsCount];
    int position;
    int half = 0;
    newPopulation = (int **)malloc(sizeof(int *) * pathsCount);
    for(int i = 0; i < pathsCount; i++) {
        newPopulation[i] = (int *)malloc(sizeof(int) * pathsLength);
    }
    // getting the lower cost to compare
    for (int i = 1; i< pathsCount; i++) {
        if (costs[i] < lowerCost) {
            lowerCost = costs[i];
            lowerPath = paths[i];
        }
    }

    bestCost = lowerCost;

    // set the part of each path in roullet
    for (int i = 1; i< pathsCount; i++) {
        roulletCounter[i] = (int)(BALANCE * lowerCost) / costs[i];
        roulletSize += roulletCounter[i];
    }

    for (int parentCounter = 0; parentCounter < pathsCount; parentCounter++) {
        // get parent 1
        int fortuneWell = rand() % roulletSize;
        int breakPoint = 0;
        for(position = 0; position < pathsCount; position++) {
            breakPoint += roulletCounter[position];
            if (breakPoint >= fortuneWell) {
                break;
            }
        }
        if (position == pathsCount) {
            position--;
        }

        int *parent1 = paths[position];
        

        // get parent 2
        fortuneWell = rand() % roulletSize;
        breakPoint = 0;
        for(position = 0; position < pathsCount; position++) {
            breakPoint += roulletCounter[position];
            if (breakPoint >= fortuneWell) {
                break;
            }
        }
        if (position == pathsCount) {
            position--;
        }

        if (paths[position] == parent1) {
            position = (position + 1) % pathsCount;
        }
        int *parent2 = paths[position];

        half = (int)(pathsCount / 2);
        for (int a = 0; a < half; a++) {
            // printf("\nparent: %d", parent1[a]);
            newPopulation[parentCounter][a] = parent1[a];
        }
        for (half; half <pathsCount; half++) {
            newPopulation[parentCounter][half] = parent2[half];
        }

        int mutationWell = rand() % 100;
        if (mutationWell == 33 || mutationWell == 20) {
            int first = rand() % pathsLength;
            int second = rand() % pathsLength;
            int aux = newPopulation[parentCounter][second];
            newPopulation[parentCounter][second] = newPopulation[parentCounter][first];
            newPopulation[parentCounter][first] = aux;

        }
    }

    paths = newPopulation;
    // getting costs ... again 
    for(int i = 1; i < pathsCount; i++) {
        int cost = 0;
        for(int j = 0; j < pathsLength; j++) {
            paths[i][j] = rand() % paths[0][pathsLength - 1];
            if (j != 0) {
                int aux = paths[i][j];
                cost+= costMatrix->getMatrix()[i][aux];
            }
            cost += costMatrix->getMatrix()[pathsLength - 1][i];
            costs[i] = cost;
        }
    }

    // getting the lower cost to compare
    for (int i = 1; i< pathsCount; i++) {
        if (costs[i] < lowerCost) {
            lowerCost = costs[i];
            lowerPath = paths[i];
        }
    }

}

void GeneticAlgorithm::printPaths() {
    for(int i = 0; i < pathsCount; i++) {
        printf("Caminho %d: ", i);
        for (int j = 0; j< pathsLength; j++) {
            printf("%3d ", paths[i][j]);
        }
        putchar('\n');
    }
    printf("\nCusto: ");
    for(int i = 0; i < pathsCount; i++) {
        printf("%5d", costs[i]);
        putchar('\n');
    }
    // printf("Caminho 0: ");
    // for(int i = 0; i < pathsLength; i++) {
    //     printf("%d, ", paths[14][i]);
    // }
}
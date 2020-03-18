#pragma once
#include "Matrix.hpp"

class GeneticAlgorithm {
    private:
        Matrix* costMatrix;
        int initIndex = 3;
        int** paths;
        int *costs;
        int pathsCount;
        int pathsLength;
        int bestCost;
        int *lowerPath;
    public:
        GeneticAlgorithm(Matrix *);
        void crossover();
        ~GeneticAlgorithm();
        void printPaths();
};
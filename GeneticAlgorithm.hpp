#pragma once
#include "Matrix.hpp"

class GeneticAlgorithm {
    private:
        Matrix* costMatrix;
        int** paths;
        int *costs;
        int pathsCount;
        int pathsLength;
    public:
        GeneticAlgorithm(Matrix *);
        ~GeneticAlgorithm();
        void printPaths();
};
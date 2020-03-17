#include "Matrix.hpp"
#include "GeneticAlgorithm.hpp"
#include <stdlib.h>
#include <stdio_ext.h>
#include <iostream>
#include <list>
using namespace std;

int main() {
    Matrix matrix("Env.txt");
    matrix.print();
    GeneticAlgorithm g(&matrix);
    g.printPaths();
    return 0;
    // for (int i = 0; i < matrix.getRows(); i++) {
    //     for (int j = 0; j < matrix.getColumns(); j++) {
    //         cout<<
    //     }
    // }
}
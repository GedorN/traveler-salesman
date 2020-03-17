#pragma once
class Matrix {
    private:
        int** matrix;
        int rows;
        int columns;
    public:
    Matrix(char* maze);
    ~Matrix();
    int** getMatrix();
    int getRows();
    int getColumns();
    void print();
};
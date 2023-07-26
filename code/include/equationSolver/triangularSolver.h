#ifndef LAB05_TRIANGULARSOLVER_H
#define LAB05_TRIANGULARSOLVER_H

#include "matrix/matrix.h"
enum TSType
{
    UPPER
};

class TriangularSolver
{
private:
    TSType type;
    Matrix T;
    Matrix B;
    Matrix OUT;
public:
    TriangularSolver(TSType type, Matrix& T, Matrix& B);
    void solve();
    void getSolution(Matrix& S);
private:
    void solveUpper();
    void solveLower();
    double getSum(int row, int col);
};
#endif //LAB05_TRIANGULARSOLVER_H

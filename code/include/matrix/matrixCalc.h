#ifndef LAB05_MATRIXCALC_H
#define LAB05_MATRIXCALC_H
#include "matrix/matrix.h"

class MatrixCalc
{
    public:
        static void subtractRows(Matrix &A, int rowA, int rowB, double scalar);
        static void subtractMatrix(Matrix &A, Matrix &B, Matrix &result);
        static void addMatrix(Matrix &A, Matrix &B,  Matrix &result);
        static void multiplyByScalar(Matrix &A, double scalar, Matrix &result);
        static void multiplyMatrix(Matrix &a, Matrix &b, Matrix &result);
        static double dotProduct(Matrix &A, Matrix &B, int row, int col);
};
#endif //LAB05_MATRIXCALC_H

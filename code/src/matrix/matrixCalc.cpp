#include <iostream>
#include "matrix/matrixCalc.h"

 void MatrixCalc::multiplyByScalar(Matrix &A, double scalar, Matrix &result)
 {
    int rowNum = A.rows();
    int colNum = A.cols();
    for(int r = 0; r < rowNum; r++)
        for(int c = 0; c < colNum; c++)
            result.set(r, c, scalar * A.get(r, c));
 }

void MatrixCalc::subtractRows(Matrix &A, int rowA, int rowB, double scalar)
{
    int colNum = A.cols();
    double nValue = 0;

    for(int i = 0; i < colNum; i++)
    {
        nValue = A.get(rowA, i) - scalar * A.get(rowB, i);
        A.set(rowA, i, nValue);
    }
}

void MatrixCalc::subtractMatrix(Matrix &A, Matrix &B, Matrix &result)
{
    if(A.rows() != B.rows() || A.cols() != B.cols())
    {
        std::cout<<"MatrixCalc::subtractMatrix Incorrect matrix size.\n";
        exit(0);
    }

    int rowN = A.rows();
    int colN = A.cols();



    for(int r = 0; r < rowN; r++)
        for(int c = 0; c < colN; c++)
            result.set(r, c, A.get(r, c) - B.get(r, c));
}

void MatrixCalc::addMatrix(Matrix &A, Matrix &B, Matrix &result)
{
    if(A.rows() != B.rows() || A.cols() != B.cols())
    {
        std::cout<<"MatrixCalc::subtractMatrix Incorrect matrix size.\n";
        exit(0);
    }

    int rowN = A.rows();
    int colN = A.cols();

    for(int r = 0; r < rowN; r++)
        for(int c = 0; c < colN; c++)
            result.set(r, c, A.get(r, c) + B.get(r, c));
}


double MatrixCalc::dotProduct(Matrix &A, Matrix &B, int row, int col)
{
    double res = 0;
    int colN = A.cols();
    for(int i = 0; i < colN; i++)
        res += A.get(row, i) * B.get(i, col);

    return res;
}

void MatrixCalc::multiplyMatrix(Matrix &A, Matrix &B, Matrix &result)
{
    if(A.cols() != B.rows())
    {
        std::cout<<"MatrixCalc::multiplyMatrix Incorrect matrix size.\n";
        exit(0);
    }

    int rowA = A.rows();
    int colB = B.cols();

    for(int r = 0; r < rowA; r++)
        for(int c = 0; c < colB; c++)
            result.set(r, c, dotProduct(A, B, r, c));
}

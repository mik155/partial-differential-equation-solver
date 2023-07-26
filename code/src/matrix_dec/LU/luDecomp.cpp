#include <iostream>
#include "matrix_dec/LU/luDecomp.h"
#include "matrix/matrixCalc.h"

LUDecomp::LUDecomp(Matrix &A) : A(A), L(A.rows(), A.cols()), U(A), P(A.rows(), A.rows())
{
    int rowNum = A.rows();
    for(int i = 0; i < rowNum; i++)
        P.set(i, i, 1);
};

void LUDecomp::decompose()
{
    int colNum = U.cols();

    for(int c = 0; c < colNum; c++)
    {
        chooseElement(c, c);
        setZeroOnRow(c, c);
    }
}
void LUDecomp::chooseElement(int row, int col)
{
    int rowMaxV = row;
    int colMaxV = col;

    if(U.get(row, col) == 0)
        findMax(&rowMaxV, &colMaxV, row, col);

    if(rowMaxV != row)
    {
        U.swapRows(row, rowMaxV);
        L.swapRows(row, rowMaxV);
        P.swapRows(row, rowMaxV);
        operations.emplace_back(OType::ROW_SWAP, row, rowMaxV);
    }

    if(colMaxV != col)
    {
        U.swapRows(col, colMaxV);
        L.swapRows(col, colMaxV);
        P.swapRows(col, colMaxV);
        operations.emplace_back(OType::COL_SWAP, col, colMaxV);
    }

}

void LUDecomp::setZeroOnRow(int row, int col)
{
    int rowNum = U.rows();
    double  diagVal = U.get(row, col);
    L.set(row, col, 1);

    row = row + 1;
    while(row < rowNum)
    {
        double scalar = U.get(row, col) / diagVal;
        MatrixCalc::subtractRows(U, row, col, scalar);
        operations.emplace_back(Operation(OType::ROW_SUBTR, row, col, scalar));
        L.set(row, col, scalar);
        row++;
    }
}

void LUDecomp::getL(Matrix& L)
{
    L = this->L;
}

void LUDecomp::getU(Matrix& U)
{
    U = this->U;
}

void LUDecomp::getP(Matrix &P)
{
    P = this->P;
}

void LUDecomp::restoreMatrix(Matrix &B)
{
    for(Operation o : operations)
    {
        if(o.getOperationType() == OType::ROW_SWAP)
            B.swapRows(o.getIndex0(), o.getIndex1());
        else if(o.getOperationType() == OType::COL_SWAP)
            B.swapCols(o.getIndex0(), o.getIndex1());
        else if(o.getOperationType() == OType::ROW_SUBTR)
            MatrixCalc::subtractRows(B, o.getIndex0(), o.getIndex1(), o.getScalar());
    }
}

void LUDecomp::findMax(int *rowI, int *colI, int startRow, int startCol)
{
    int rowNum = U.rows();
    int colNum = U.cols();

    *rowI = startRow;
    *colI = startCol;

    //TODO, NA RAZIE TYLKO WYBÓR PODSTAWOWY
    for(int r = startRow; r < rowNum; r++)
        for(int c = startCol; c == startCol; c++)
        {
            if(abs(U.get(*rowI, *colI)) < abs(U.get(r, c)))
            {
                *rowI = r;
                *colI = c;
            }
        }
}

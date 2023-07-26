#include <cstring>
#include <iostream>
#include "matrix/matrix.h"

Matrix::Matrix(const Matrix &matrix)
{
    this->rowNum = matrix.rowNum;
    this->colNum = matrix.colNum;

    this->data = new double [rowNum * colNum];
    memcpy(this->data, matrix.data,  rowNum * colNum * sizeof(double));

    this->rowI = new int [rowNum];
    memcpy(this->rowI, matrix.rowI,  rowNum * sizeof(int));

    this->colI = new int [colNum];
    memcpy(this->colI, matrix.colI,  colNum * sizeof(int));
}

Matrix::Matrix(double data [], int row, int col)
{
    rowNum = row;
    colNum = col;

    this->data = new double [row * col];
    memcpy(this->data, data,  row * col * sizeof(double));

    rowI = new int [rowNum];
    for(int i = 0; i < rowNum; i++)
        rowI[i] = i;

    colI = new int [colNum];
    for(int i = 0; i < colNum; i++)
        colI[i] = i;
}

Matrix::Matrix(int row, int col)
{
    rowNum = row;
    colNum = col;

    data = new double [row * col];
    memset(data, 0, row * col * sizeof(double));

    rowI = new int [rowNum];
    for(int i = 0; i < rowNum; i++)
        rowI[i] = i;

    colI = new int [colNum];
    for(int i = 0; i < colNum; i++)
        colI[i] = i;
}

Matrix::~Matrix()
{
    delete [] data;
    delete [] rowI;
    delete [] colI;
}

double Matrix::get(int row, int col)
{
    if(!hasRow(row) || !hasCol(col))
    {
        std::cout<<"Matrix index out of bound !\n";
        exit(0);
    }

    return data[rowI[row] * colNum + colI[col]];
}

void Matrix::setValues(double data [], int size)
{
    if(size != rowNum * colNum)
    {
        std::cout<<"Matrix index out of bound !\n";
        exit(0);
    }

    memcpy((void*) this->data, (void*) data,  size * sizeof(double));
}

void Matrix::set(int row, int col, double val)
{
    if(!hasRow(row) || !hasCol(col))
    {
        std::cout<<"Matrix index out of bound !\n";
        exit(0);
    }

    data[rowI[row] * colNum + colI[col]] = val;
}

void Matrix::swapRows(int rowA, int rowB)
{
    if(!hasRow(rowA) || !hasRow(rowB))
    {
        std::cout<<"Matrix index out of bound !\n";
        exit(0);
    }

    std::swap(*(rowI + rowA), *(rowI + rowB));
}

void Matrix::swapCols(int colA, int colB)
{
    if(!hasCol(colA) || !hasCol(colB))
    {
        std::cout<<"Matrix index out of bound !\n";
        exit(0);
    }

    std::swap(*(colI + colA), *(colI + colB));
}

std::string Matrix::toString()
{
    std::string out;
    for(int r = 0; r < rowNum; r++)
    {
        out += " ";
        for(int c = 0; c < colNum; c++)
            out += std::to_string(get(r, c)) + " ";
        out += "\n";
    }

    return out;
}

int Matrix::cols()
{
    return colNum;
}

int Matrix::rows()
{
    return rowNum;
}

bool Matrix::hasRow(int rowI)
{
    return rowI < rowNum && rowI >= 0;
}

bool Matrix::hasCol(int colI)
{
    return colI < colNum && colI >= 0;
}

bool Matrix::operator==(Matrix& matrix)
{
    int rowNum = matrix.rows();
    int colNum = matrix.cols();

    if(this->rowNum != rowNum || this->colNum != colNum)
        return false;

    for(int r = 0; r < rowNum; r++)
        for(int c = 0; c < colNum; c++)
        {
            if (get(r, c) != matrix.get(r, c)) {
                return false;
            }
        }

    return true;
}

void Matrix::operator=(Matrix& matrix)
{

    int rowNum = matrix.rows();
    int colNum = matrix.cols();

    if(this->rowNum != rowNum || this->colNum != colNum)
    {
        std::cout<<"Incorrect array size.\n";
        exit(0);
    }

    memcpy(this->data, matrix.data,  rowNum * colNum * sizeof(double));
    memcpy(this->rowI, matrix.rowI,  rowNum * sizeof(int));
    memcpy(this->colI, matrix.colI,  colNum * sizeof(int));
}

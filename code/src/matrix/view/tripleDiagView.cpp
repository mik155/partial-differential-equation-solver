#include <iostream>
#include "matrix/view/tripleDiagView.h"

TripleDiagView::TripleDiagView(Matrix& M, int size) : Matrix(M)
{
    if(M.cols() != 3 || (M.cols() * M.rows() != 3 * size))
    {
        std::cout<<"TripleDiagView::: Incorrect matrix size.\n";
        exit(0);
    }
}

void TripleDiagView::set(int row, int col, double val)
{
    if(checkIndexOutOfBound(row, col))
    {
        std::cout<<"TripleDiagView::Matrix index out of bound !\n";
        exit(0);
    }

    if(checkIllegalSet(row, col))
    {
            std::cout<<"TripleDiagView::This value must equal 0 ! !\n";
            exit(0);
    }

    Matrix::set(row, col - transl(row), val);
}

double TripleDiagView::get(int row, int col)
{
    if(checkIndexOutOfBound(row, col))
    {
        std::cout<<"TripleDiagView::Matrix index out of bound !\n";
        exit(0);
    }

    if(checkIllegalSet(row, col))
        return 0;

    return Matrix::get(row, col - transl(row));
}

bool TripleDiagView::checkIllegalSet(int row, int col)
{
    int size = Matrix::rows() - 1;

    int lastRow = size - 1;
    int lastCol = size - 1;

    if( row == 0  && col > 1)
        return true;

    if( row == lastRow  &&  col < (lastCol - 1) )
        return true;

    if( row != col && col != (row - 1) && col != (row + 1) )
        return true;

    return false;
}

bool TripleDiagView::checkIndexOutOfBound(int row, int col)
{
    int size = Matrix::rows() - 1;

    return row < 0 || row > size || col < 0 || col > size;
}

int TripleDiagView::transl(int row)
{
    return row < 2 ? 0 : row - 1;
}

int TripleDiagView::getSize()
{
    int size = Matrix::rows() - 1;
    return size;
}

std::string TripleDiagView::toString()
{
    int size = Matrix::rows() - 1;
    std::string out;
    for(int r = 0; r < size; r++)
    {
        for(int c = 0; c < size; c++)
            out += std::to_string(get(r, c)) + " ";
        out += "\n";
    }

    return out;
}

int TripleDiagView::rows()
{
    return this->rowNum;
}

int TripleDiagView::cols()
{
    return this->rowNum;
}

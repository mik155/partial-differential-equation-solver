#include "equationSolver/triangularSolver.h"

TriangularSolver::TriangularSolver(TSType type, Matrix& T, Matrix& B) : T(T), B(B), OUT(B.rows(), B.cols())
{
    this->type = type;
}

void TriangularSolver::solve()
{
    if(type == TSType::UPPER)
        solveUpper();
}

void TriangularSolver::solveUpper()
{
    int rowNum = OUT.rows();
    for(int i = rowNum - 1; i >= 0; i--)
        OUT.set(i, 0, (B.get(i, 0) - getSum(i, i) ) / T.get(i, i));
}

void TriangularSolver::solveLower()
{

}

double TriangularSolver::getSum(int row, int col)
{
    int colNum = T.cols();
    double sum = 0;
    for(int i = col + 1; i < colNum; i++)
        sum += T.get(row, i) * OUT.get(i, 0);
    return sum;
}

void TriangularSolver::getSolution(Matrix& S)
{
    S = this->OUT;
}

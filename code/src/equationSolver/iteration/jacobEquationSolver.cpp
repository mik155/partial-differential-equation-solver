#include <iostream>
#include "equationSolver/iteration/jacobEquationSolver.h"


JacobEquationSolver::JacobEquationSolver(Matrix* A, Matrix* B, Matrix* x0) : EquationIterativeSolver(A, B, x0), tmp(A->cols(), 1)
{

}

double JacobEquationSolver::sigma(int i)
{
    int n = A->cols();
    double res = 0;
    for(int j = 0; j < n; j++)
        if(j != i)
            res += A->get(i, j) * x0->get(j, 0);
    return res;
}

void JacobEquationSolver::next(int M)
{
    double a_ii;
    double b_i;
    int colNum = A->cols();

    for(int k = 0; k < M; k++)
    {
        for (int i = 0; i < colNum; i++)
        {
            a_ii = A->get(i, i);
            b_i = B->get(i, 0);
            tmp.set(i, 0, (b_i - sigma(i)) / a_ii);
        }

        *x0 = tmp;
        step++;
    }
}

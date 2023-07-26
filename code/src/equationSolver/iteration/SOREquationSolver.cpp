#include "equationSolver/iteration/SOREquationSolver.h"

SOREquationSolver::SOREquationSolver(Matrix* A, Matrix* B, Matrix* x0, double omega)
: EquationIterativeSolver(A, B, x0)
{
    this->omega = omega;
}

void SOREquationSolver::next(int M)
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
            x0->set(i, 0, ((1.0 - omega) * x0->get(i, 0)) + ((b_i - sigma(i)) * omega) / a_ii);
        }
        step++;
    }
}

double SOREquationSolver::sigma(int i)
{
    int n = A->cols();
    double res = 0;
    for(int j = 0; j < n; j++)
        if(j != i)
            res += A->get(i, j) * x0->get(j, 0);
    return res;
}

#include "equationSolver/iteration/gausSeidelEquationSolver.h"
#include <cmath>
GausSeidelEquationSolver::GausSeidelEquationSolver(Matrix* A, Matrix* B, Matrix* x0)
: EquationIterativeSolver(A, B, x0)
{

}

void GausSeidelEquationSolver::next(int M)
{
    double a_ii;
    double b_i;
    int colNum = A->cols();

    Matrix prev(*x0);

    for(int k = 1; k < M; k++)
    {
        for (int i = 0; i < colNum; i++)
        {
            a_ii = A->get(i, i);
            b_i = B->get(i, 0);
            x0->set(i, 0, (b_i - sigma(i)) / a_ii);
        }

        if(finish(k, prev))
            return;

        step++;
    }
}

bool GausSeidelEquationSolver::finish(int k, Matrix& prev)
{

    if(check_period > 0)
    {
        if (k % check_period == 0)
        {
            prev = *x0;
        }
        else if ((k + 1) % check_period == 0)
            if (stopCondition(prev, *x0))
                return true;
    }
    return false;
}

bool GausSeidelEquationSolver::stopCondition(Matrix& prev, Matrix& actual)
{
    if(TOLX > 0)
    {
        for(int i = 0; i < prev.rows(); i++)
        {
            if(std::abs(prev.get(i,0) - actual.get(i,0)) > TOLX)
                return false;
        }
        return true;
    }
    return false;
}

double GausSeidelEquationSolver::sigma(int i)
{
    int n = A->cols();
    double res = 0;
    for(int j = 0; j < n; j++)
        if(j != i)
            res += A->get(i, j) * x0->get(j, 0);
    return res;
}

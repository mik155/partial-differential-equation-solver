#include "equationSolver/iteration/equationIterativeSolver.h"
#include "matrix/matrixCalc.h"

EquationIterativeSolver::EquationIterativeSolver(Matrix *A, Matrix *B, Matrix* x0) : A(A), B(B),
x0(x0)
{
    step = 0;
}

Matrix* EquationIterativeSolver::getSolution()
{
    return x0;
}

void EquationIterativeSolver::getResiduum(Matrix& dest)
{
    Matrix residuum(A->rows(), 1);
    //residuum = A * x0
    MatrixCalc::multiplyMatrix(*A, *x0, residuum);
    //residuum = - A * x0
    MatrixCalc::multiplyByScalar(residuum, -1, residuum);
    //residuum = B - A * x0
    MatrixCalc::addMatrix(*B, residuum, residuum);
    dest = residuum;
}


unsigned int EquationIterativeSolver::getStep()
{
    return step;
}

void EquationIterativeSolver::setTOLX(double val)
{
    this->TOLX = val;
}

void EquationIterativeSolver::setCheckPeriod(int val)
{
    this->check_period = val;
}

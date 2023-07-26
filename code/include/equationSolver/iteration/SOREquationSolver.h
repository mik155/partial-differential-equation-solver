#ifndef LAB05_SOREQUATIONSOLVER_H
#define LAB05_SOREQUATIONSOLVER_H

#include "equationIterativeSolver.h"

class SOREquationSolver : public EquationIterativeSolver
{
public:
    SOREquationSolver(Matrix* A, Matrix* B, Matrix* x0, double omega);
    void next(int n);

private:
    double omega;
    double sigma(int i);
};
#endif //LAB05_SOREQUATIONSOLVER_H

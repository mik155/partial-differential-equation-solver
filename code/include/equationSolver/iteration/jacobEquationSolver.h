#ifndef LAB05_JACOBEQUATIONSOLVER_H
#define LAB05_JACOBEQUATIONSOLVER_H

#include "equationIterativeSolver.h"

class JacobEquationSolver : public EquationIterativeSolver
{
    public:
        JacobEquationSolver(Matrix* A, Matrix* B, Matrix* x0);
        void next(int n);

    private:
        Matrix tmp;
        double sigma(int i);
};
#endif //LAB05_JACOBEQUATIONSOLVER_H

#ifndef LAB05_GAUSSEIDELEQUATIONSOLVER_H
#define LAB05_GAUSSEIDELEQUATIONSOLVER_H

#include "equationIterativeSolver.h"

class GausSeidelEquationSolver : public EquationIterativeSolver
{

public:
    GausSeidelEquationSolver(Matrix* A, Matrix* B, Matrix* x0);
    void next(int n);

private:
    bool finish(int k, Matrix& prev);
    double sigma(int i);
    bool stopCondition(Matrix& prev, Matrix& actual);
};
#endif //LAB05_GAUSSEIDELEQUATIONSOLVER_H

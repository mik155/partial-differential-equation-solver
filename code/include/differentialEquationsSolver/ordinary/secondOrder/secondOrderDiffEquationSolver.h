#ifndef LAB05_SECONDORDERDIFFEQUATIONSOLVER_H
#define LAB05_SECONDORDERDIFFEQUATIONSOLVER_H

#include "utils/intervals/closedInterval.h"
#include "differentialEquationsSolver/mesh.h"

class SecondOrderDifferentiaEquationSolver
{
    private:
        Mesh mesh;
        Matrix A;

    public:
        SecondOrderDifferentiaEquationSolver(double initValues[4], double diagValues[3], Mesh& mesh);
        void solve(Matrix& B);
};

#endif //LAB05_SECONDORDERDIFFEQUATIONSOLVER_H

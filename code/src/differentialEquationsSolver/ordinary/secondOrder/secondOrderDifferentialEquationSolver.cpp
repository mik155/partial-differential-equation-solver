#include <iostream>
#include "differentialEquationsSolver/ordinary/secondOrder/secondOrderDiffEquationSolver.h"
#include "matrix/view/tripleDiagView.h"
#include "equationSolver/thomasSolver.h"

SecondOrderDifferentiaEquationSolver::SecondOrderDifferentiaEquationSolver(double initValues[4], double diagValues [3], Mesh& mesh) :
        mesh(mesh),
        A( mesh.getXPointsNum() , 3)

{
    int rows = A.rows();

    A.set(0,2, -100);

    //Ustawiam warunki początkowe
    A.set(0, 0, initValues[0]);
    A.set(0, 1, initValues[1]);

    A.set(rows - 1, 0, initValues[2]);
    A.set(rows - 1, 1, initValues[3]);

    for(int i  = 1; i < rows -1; i++)
    {
        A.set(i, 0, diagValues[0]);
        A.set(i, 1, diagValues[1]);
        A.set(i, 2, diagValues[2]);
    }
}

void SecondOrderDifferentiaEquationSolver::solve(Matrix &B)
{
    TripleDiagView mView(A, A.rows());
    //std::cout<<mView.toString();
    //std::cout<<B.toString();

    ThomasSolver solver(mView);
    solver.calculateDiagonal();
    solver.getResult(B);
}

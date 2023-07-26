#include <iostream>
#include "equationSolver/thomasSolver.h"
#include "matrix/matrixCalc.h"

ThomasSolver::ThomasSolver(TripleDiagView &M_VIEW) : M_VIEW(M_VIEW)
{

}

void ThomasSolver::solve()
{
    calculateDiagonal();
}

void ThomasSolver::calculateDiagonal()
{
    int diagSize = M_VIEW.getSize();

    double d_i;
    double d_ip;
    double l_i;
    double u_ip;

    for(int i = 1; i < diagSize; i++)
    {
        d_i = M_VIEW.get(i, i);
        d_ip = M_VIEW.get(i - 1, i - 1);
        l_i = M_VIEW.get(i, i - 1);
        u_ip = M_VIEW.get(i - 1, i);

        M_VIEW.set(i,i, d_i - ((l_i * u_ip)/ d_ip) );
    }

}

void ThomasSolver::getResult(Matrix  &B)
{
    int diagSize = M_VIEW.getSize();


    double b_i;
    double l_i;
    double d_ip;
    double r_ip;

    for(int i = 1; i < diagSize; i++)
    {
        b_i = B.get(i, 0);
        l_i = M_VIEW.get(i, i - 1);
        d_ip = M_VIEW.get(i - 1, i - 1);
        r_ip = B.get(i - 1, 0);

        B.set(i,0, b_i - ((l_i * r_ip)/ d_ip) );
    }

    double r_i;
    double d_i;
    double u_i;
    double x_in;

    r_i = B.get(diagSize - 1, 0);
    d_i = M_VIEW.get(diagSize - 1, diagSize - 1);

    B.set(diagSize - 1, 0, r_i / d_i);
    for(int i = diagSize - 2; i >= 0; i--)
    {
        d_i = M_VIEW.get(i, i);
        r_i = B.get(i, 0);
        u_i = M_VIEW.get(i, i + 1);
        x_in = B.get(i + 1, 0);

        B.set(i, 0, (r_i - u_i * x_in) / d_i);
    }

}

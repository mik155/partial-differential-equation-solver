#ifndef LAB05_EQUATIONITERATIVESOLVER_H
#define LAB05_EQUATIONITERATIVESOLVER_H

#include "matrix/matrix.h"

class EquationIterativeSolver
{
    protected:
        double TOLX = -1;
        int check_period;
        unsigned int step;


        Matrix* A;
        Matrix* B;
        Matrix* x0;

    public:
        EquationIterativeSolver(Matrix* A, Matrix* B, Matrix* x0);
        unsigned int getStep();
        Matrix* getSolution();
        void getResiduum(Matrix& dest);
        virtual void next(int n = 1) =0;
        void setTOLX(double val);
        void setCheckPeriod(int vla);
};
#endif //LAB05_EQUATIONITERATIVESOLVER_H

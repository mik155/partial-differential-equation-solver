//
// Created by mik15 on 24.04.2022.
//

#ifndef LAB05_LUDECOMP_H
#define LAB05_LUDECOMP_H

#include <list>
#include "matrix/matrix.h"
#include "operation.h"

class LUDecomp
{
    friend class LUDecompTest;

    private:
        Matrix A;
        Matrix P;
        Matrix L;
        Matrix U;

        std::list<Operation> operations;

    public:
        LUDecomp(Matrix& A);
        void decompose();
        void getL(Matrix& L);
        void getU(Matrix& U);
        void getP(Matrix& P);
        void restoreMatrix(Matrix& B);
        void setZeroOnRow(int row, int col);

private:
        void findMax(int* rowI, int* colI, int startRow, int startCol);
        void chooseElement(int row, int col);
};
#endif //LAB05_LUDECOMP_H

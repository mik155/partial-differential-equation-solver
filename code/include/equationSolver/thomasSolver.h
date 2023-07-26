#ifndef LAB05_THOMASSOLVER_H
#define LAB05_THOMASSOLVER_H

#include <list>
#include "matrix/matrix.h"
#include "matrix_dec/LU/operation.h"
#include "matrix/view/tripleDiagView.h"

class ThomasSolver
{
private:
    TripleDiagView M_VIEW;

public:
    ThomasSolver(TripleDiagView& M_VIEW);
    void solve();

    void calculateDiagonal();
    void getResult(Matrix  &B);

};
#endif //LAB05_THOMASSOLVER_H

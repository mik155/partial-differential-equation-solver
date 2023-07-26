#ifndef LAB05_TRIPLEDIAGVIEW_H
#define LAB05_TRIPLEDIAGVIEW_H
#include "matrix/matrix.h"
class TripleDiagView : public Matrix
{
public:
    TripleDiagView(Matrix& M, int diagSize);
    int getSize();
    void set(int row, int col, double val);
    double get(int row, int col);
    int rows();
    int cols();
    std::string toString();

private:
    bool checkIndexOutOfBound(int row, int col);
    bool checkIllegalSet(int row, int col);
    int transl(int row);
};
#endif //LAB05_TRIPLEDIAGVIEW_H

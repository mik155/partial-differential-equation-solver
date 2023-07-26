#ifndef LAB05_MATRIX_H
#define LAB05_MATRIX_H

#include <string>

class Matrix
{
    friend class MatrixTest;

    protected:
        double* data;
        int* rowI;
        int* colI;

        int rowNum;
        int colNum;

    public:
        Matrix(const Matrix& matrix);
        Matrix(double data [], int row, int col);
        Matrix(int row, int col);
        ~Matrix();

        virtual double get(int row, int col);
        virtual void set(int row, int col, double val);

        virtual int rows();
        virtual int cols();

        void swapRows(int rowA, int rowB);
        void swapCols(int colA, int colB);

        bool hasRow(int rowI);
        bool hasCol(int colI);

        bool operator==(Matrix& matrix);
        void operator=(Matrix& matrix);

        void setValues(double data[], int size);

    virtual std::string toString();
};
#endif //LAB05_MATRIX_H

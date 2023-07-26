#include "matrix_dec/LU/operation.h"

Operation::Operation(OType type, int i0, int i1, double sc)
{
    this->type = type;
    this->index0 = i0;
    this->index1 = i1;
    this->scalar = sc;
}

Operation::Operation(OType type, int i0, int i1)
{
    this->type = type;
    this->index0 = i0;
    this->index1 = i1;
    this->scalar = 0;
}

OType Operation::getOperationType()
{
    return type;
}

int Operation::getIndex0()
{
    return index0;
}

int Operation::getIndex1()
{
    return index1;
}

double Operation::getScalar()
{
    return scalar;
}

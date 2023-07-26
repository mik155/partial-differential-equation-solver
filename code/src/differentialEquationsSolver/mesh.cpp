#include <iostream>
#include "differentialEquationsSolver/mesh.h"

Mesh::Mesh(ClosedInterval X_INTERVAL, double X_DELTA, ClosedInterval Y_INTERVAL, double Y_DELTA)
: X_INTERVAL(X_INTERVAL), X_DELTA(X_DELTA), X_POINTS_NUM(int (X_INTERVAL.size() / X_DELTA + 1)),
  Y_INTERVAL(Y_INTERVAL), Y_DELTA(Y_DELTA), Y_POINTS_NUM(int (Y_INTERVAL.size() / Y_DELTA + 1))
{

}

double Mesh::getX(double index)
{
    if(index >= X_POINTS_NUM)
    {
        std::cout<<"MESH ERROR ! INDEX OUT OF BOUND [X]!";
        exit(0);
    }
    return X_INTERVAL.left() + index * X_DELTA;
}

double Mesh::getY(double index)
{
    if(index >= Y_POINTS_NUM)
    {
        std::cout<<"MESH ERROR ! INDEX OUT OF BOUND [Y]!";
        exit(0);
    }
    return Y_INTERVAL.left() + index * Y_DELTA;
}

double Mesh::getYPointsNum()
{
    return Y_POINTS_NUM;
}

double Mesh::getXPointsNum()
{
    return X_POINTS_NUM;
}

double Mesh::getDeltaX()
{
    return X_DELTA;
}

double Mesh::getDeltaY()
{
    return Y_DELTA;
}


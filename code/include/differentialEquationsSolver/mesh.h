//
// Created by mik15 on 27.05.2022.
//

#ifndef LAB05_MESH_H
#define LAB05_MESH_H

#include "matrix/matrix.h"
#include "utils/intervals/closedInterval.h"

class Mesh
{
    private:
        ClosedInterval X_INTERVAL;
        double X_DELTA;
        double X_POINTS_NUM;

        ClosedInterval Y_INTERVAL;
        double Y_DELTA;
        double Y_POINTS_NUM;

public:
    Mesh(ClosedInterval X_INTERVAL, double X_DELTA, ClosedInterval Y_INTERVAL, double Y_DELTA);
    double getX(double index);
    double getY(double index);
    double getYPointsNum();
    double getXPointsNum();
    double getDeltaX();
    double getDeltaY();
};
#endif //LAB05_MESH_H

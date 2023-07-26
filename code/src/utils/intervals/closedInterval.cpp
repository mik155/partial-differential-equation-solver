#include "utils/intervals/closedInterval.h"

ClosedInterval::ClosedInterval(double lBorder, double rBorder)
{
    this->leftB = lBorder;
    this->rightB = rBorder;
}

ClosedInterval::ClosedInterval(const ClosedInterval &interval)
{
    this->leftB = interval.leftB;
    this->rightB = interval.rightB;
}

bool ClosedInterval::contains(double x) const
{
    return x >= leftB && x <= rightB;
}

double ClosedInterval::size() const
{
    return rightB - leftB;
}

double ClosedInterval::left() const {
    return leftB;
}

double ClosedInterval::right() const
{
    return rightB;
}

double ClosedInterval::lower() const
{
    return leftB;
}

double ClosedInterval::upper() const
{
    return rightB;
}

void ClosedInterval::setLeftBorder(double left)
{
    leftB = left;
}

void ClosedInterval::setRightBorder(double right)
{
    rightB = right;
}
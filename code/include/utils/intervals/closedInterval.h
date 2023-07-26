#ifndef LAB05_CLOSEDINTERVAL_H
#define LAB05_CLOSEDINTERVAL_H
class ClosedInterval
{
private:
    double leftB;
    double rightB;
public:
    ClosedInterval(double lBorder, double rBorder);
    ClosedInterval(const ClosedInterval& interval);
    bool contains(double x) const;
    double size() const;
    double left() const;
    double right() const;
    double lower() const;
    double upper() const;
    void setLeftBorder(double left);
    void setRightBorder(double left);

};
#endif //LAB05_CLOSEDINTERVAL_H

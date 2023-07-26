//
// Created by mik15 on 24.04.2022.
//

#ifndef LAB05_OPERATION_H
#define LAB05_OPERATION_H
enum OType
{
    ROW_SUBTR,
    COL_SWAP,
    ROW_SWAP
};

class Operation
{
    private:
        OType type;
        int index0;
        int index1;
        double scalar;

    public:
        Operation(OType type, int i0, int i1, double sc);
        Operation(OType type, int i0, int i1);

        OType getOperationType();
        int getIndex0();
        int getIndex1();
        double getScalar();
};
#endif //LAB05_OPERATION_H

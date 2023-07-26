#ifndef LAB05_UTILS_H
#define LAB05_UTILS_H
#include <cmath>
class Utils
{
    public:
        template<typename T>
        static bool compareArrays(T* array0, T* array1, int len)
        {
            for(int i = 0; i < len; i++)
                if(array0[i] != array1[i])
                    return false;

            return true;
        }

    static double perfectSolution(double x, double t)
    {
        return exp(- M_PI * M_PI * t) * sin(M_PI * x);
    }
};
#endif //LAB05_UTILS_H

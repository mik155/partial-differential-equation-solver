#ifndef LAB05_KMBSOLVER_H
#define LAB05_KMBSOLVER_H

#include "utils/intervals/closedInterval.h"
#include "matrix/matrix.h"
#include "differentialEquationsSolver/mesh.h"

class KMBSolver
{
    private:
        double (*lCond) (double t);
        double (*rCond) (double t);
        double (*bottomCond) (double x);
        Matrix data;
        Mesh mesh;
        double D;
        double lambda;

    void solveRow(int row);


public:
        /**
         * Konstruktor inicjalizujący klasę
         *
         * @param hInterval przedział poziomy (oś x), w którym rozwiązujemy równanie
         * @param tInterval przedział pionowy (oś y), w którym rozwiązujemy równanie
         * @param D współczynni dyfuzji równania
         * @param lCond lewy warunek brzegowy
         * @param rCond prawy warunek brzegowy
         * @param bottomCond warunek początkowy
         * */
        KMBSolver(ClosedInterval& hInterval, double deltaH,
                  ClosedInterval& tInterval, double deltaT,
                  double D,
                  double (*lCond) (double t),
                  double (*rCond) (double t),
                  double (*bottomCond) (double x));

        /**
        * Funkcja rozwiązuje równanie różniczkowe i zapisuje wynik do pliku.
        * Jako wynik, w tym przpadku, rozumiemy maksymalny błąd bezwzględny dla t = t_max
        *
        * @param appendResultToFile true - jeżeli chcemy zapisać wynik do pliku, w przeciwnym razie false
        * @param path ścieżka do pliku, w którym zostanie zapisany wynik.
        * */
        void solve(bool appendResultToFile, std::string path);

        /**
        * Zwraca ostatni oblicznoy wiersz.
        *
        * @result ostatni obliczony wiersz.
        * */
        Matrix& getSolution();
};
#endif //LAB05_KMBSOLVER_H

#ifndef LAB05_LaasonenSolver_H
#define LAB05_LaasonenSolver_H

#include "utils/intervals/closedInterval.h"
#include "matrix/matrix.h"
#include "differentialEquationsSolver/mesh.h"
#include "matrix/view/tripleDiagView.h"
#include "equationSolver/thomasSolver.h"
#include "equationSolver/iteration/gausSeidelEquationSolver.h"

class LaasonenSolver
{
    private:
        double (*lCond) (double t);
        double (*rCond) (double t);
        double (*bottomCond) (double x);
        Matrix data;
        Matrix A;
        Mesh mesh;
        double D;
        double lambda;


        void solveRow(int row, ThomasSolver& solver);
        void solveRow(int row, GausSeidelEquationSolver& solver);
        TripleDiagView* tViewInit();

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
        LaasonenSolver(ClosedInterval& hInterval, double deltaH,
                  ClosedInterval& tInterval, double deltaT,
                  double D,
                  double (*lCond) (double t),
                  double (*rCond) (double t),
                  double (*bottomCond) (double x));

        /**
        * Funkcja rozwiązuje równanie różniczkowe, korzystając z algorytmu Thomasa, i zapisuje wynik do pliku.
        * Jako wynik, w tym przpadku, rozumiemy maksymalny błąd bezwzględny dla t = t_max
        *
        * @param appendResultToFile true - jeżeli chcemy zapisać wynik do pliku, w przeciwnym razie false
        * @param path ścieżka do pliku, w którym zostanie zapisany wynik.
        * */
        void solveUsingThomasAlgorithm(bool appendResultToFile, std::string path = "");

        /**
        * Funkcja rozwiązuje równanie różniczkowe, korzystając z algorytmu Gausa-Seidela, i zapisuje wynik do pliku.
        * Jako wynik, w tym przpadku, rozumiemy maksymalny błąd bezwzględny dla t = t_max
        *
        * @param appendResultToFile true - jeżeli chcemy zapisać wynik do pliku, w przeciwnym razie false
        * @param path ścieżka do pliku, w którym zostanie zapisany wynik.
        * */
        void solveUsingGaussSeidelAlgorithm(bool appendResultToFile, std::string path = "");

        /**
        * Zwraca ostatni oblicznoy wiersz.
        *
        * @result ostatni obliczony wiersz.
        * */
        Matrix& getSolution();
};
#endif //LAB05_LaasonenSolver_H

#include <iostream>
#include <fstream>
#include <chrono>

#include "differentialEquationsSolver/partial/secondOrder/LaasonenSolver.h"
#include "equationSolver/thomasSolver.h"
#include "equationSolver/iteration/gausSeidelEquationSolver.h"
#include "utils/Utils.h"

LaasonenSolver::LaasonenSolver(
        ClosedInterval& hInterval,
        double deltaH,
        ClosedInterval& tInterval,
        double deltaT,
        double D,
        double (*lCond)(double),
        double (*rCond)(double),
        double (*bottomCond)(double)
): mesh(hInterval, deltaH, tInterval, deltaT),
   D(D), lCond(lCond), rCond(rCond), bottomCond(bottomCond),lambda(D * deltaT / (deltaH * deltaH)),
   data( int (hInterval.size() / deltaH + 1), 1),
   A( int (hInterval.size() / deltaH + 1), 3)
{
    A.set(0,0, 1.0);
    A.set(A.rows() - 1,1, 1.0);

    A.set(0,0, 1.0);
    A.set(0,1, 0.0);

    double d1 = lambda;
    double d2 = -(1.0 + 2.0 * lambda);
    double d3 = lambda;
    for(int i = 1; i <  A.rows() - 1; i++)
    {
        A.set(i, 0, d1);
        A.set(i, 1, d2);
        A.set(i, 2, d3);
    }

    A.set(A.rows() - 1 ,0, 0.0);
    A.set(A.rows() - 1,1, 1.0);
}


/**
 * Funkcja oblicza wartości w danym wierszu siatki. Korzysta z algorytmu Thomasa.
 * Wynik zapisuje w macierzy "data".
 *
 * @param row wiersz siatki
 * @param solver instancja solver'a rozwiązującego równanie.
 * */
void LaasonenSolver::solveRow(int row, ThomasSolver& solver)
{
    int rows = (int) mesh.getXPointsNum();
    for(int i = 0; i < rows; i++)
    {
        data.set(i, 0, -data.get(i, 0));
    }

    data.set(0, 0,  0.0);
    data.set(data.rows() - 1, 0,  0.0);

    solver.getResult(data);
}

void LaasonenSolver::solveUsingThomasAlgorithm(bool appendResultToFile, std::string path)
{
    //ilość zapisów do pliku wykonanych przez funkcje
    static int save = 0;

    //start pomioru czasu
    auto start = std::chrono::steady_clock::now();

    //inicjalizacja widoku
    TripleDiagView* view = tViewInit();
    ThomasSolver solver(*view);
    //operacja na macierzy A, wspólna dla rozwiązywania pozostałych układów.
    solver.calculateDiagonal();

    //inicjalizacja z warunku początkowego
    for(int i = 0; i < data.rows(); i++)
        data.set(i, 0, bottomCond(mesh.getX(i)));

    //rozwiązywanie równania
    int levels = (int ) mesh.getYPointsNum();
    for(int t = 1; t < levels; t++)
        solveRow(t, solver);

    //koniec pomiaru czasu
    auto end = std::chrono::steady_clock::now();

    //zapis wyniku do pliku
    if(appendResultToFile)
    {
        std::ofstream file(path, std::ios::app);

        std::cout<<"zapis "<<save++<<std::endl;
        double maxAbsoluteError = 0;
        double t = mesh.getY(levels - 1);
        for(int i = 0; i < mesh.getXPointsNum(); i++)
        {
            double tmp;
            double x = mesh.getX(i);
            tmp = std::abs(Utils::perfectSolution(x, t) - data.get(i, 0));
            if(tmp > maxAbsoluteError)
                maxAbsoluteError = tmp;
        }
        file<<"lamda = "<<lambda<<" t = "<<t<<" delta h = "<<mesh.getDeltaX()<<" BBW = "<<maxAbsoluteError
                  << " obliczenia zajely = "<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<<" sec\n";
        file.close();

    }

    delete view;
}

void LaasonenSolver::solveUsingGaussSeidelAlgorithm(bool appendResultToFile, std::string path)
{
    //ilość zapisów do pliku wykonanych przez funkcje
    static int save = 0;

    //start pomioru czasu
    auto start = std::chrono::steady_clock::now();

    //inicjalizacja z warunku początkowego
    for(int i = 0; i < data.rows(); i++)
        data.set(i, 0, bottomCond(mesh.getX(i)));

    //Inicjalizacja widoku i solvera
    Matrix solution(data);
    TripleDiagView* view = tViewInit();
    GausSeidelEquationSolver solver(view, &data, &solution);

    //rozwiązywanie równania
    int levels = (int) mesh.getYPointsNum();
    for(int t = 1; t < levels; t++)
    {
        solveRow(t, solver);
        data = solution;
    }

    //koniec pomiaru czasu
    auto end = std::chrono::steady_clock::now();

    //zapis wyniku do pliku
    if(appendResultToFile)
    {
        std::ofstream file(path, std::ios::app);
        std::cout<<"zapis "<<save++<<std::endl;
        double maxAbsoluteError = 0;
        double t = mesh.getY(levels - 1);
        for(int i = 0; i < mesh.getXPointsNum(); i += 1)
        {
            double tmp;
            double x = mesh.getX(i);
            tmp = std::abs(Utils::perfectSolution(x, t) - data.get(i, 0));
            if(tmp > maxAbsoluteError)
                maxAbsoluteError = tmp;
        }

    file<<"lamda = "<<lambda<<" t = "<<t<<" delta h = "<<mesh.getDeltaX()<<" BBW = "<<maxAbsoluteError
        << " obliczenia zajely = "<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<<" sec\n";
    file.close();
    }

    delete view;
}

Matrix& LaasonenSolver::getSolution()
{
    return data;
}

/**
 * Funkcja inicjalizaująca widok macierzy A, wykorzystywanej w obliczeniach.
 * */
TripleDiagView *LaasonenSolver::tViewInit()
{
    TripleDiagView* view = new TripleDiagView(A, A.rows());
    return view;
}


/**
 * Funkcja oblicza wartości w danym wierszu siatki. Korzysta z algorytmu Gausa-Seidela.
 * Wynik zapisuje w macierzy zdefiniowanej w instancji klasy GausSeidelEquationSolver, którą
 * przesyłamek przez referencje.
 *
 * @param row wiersz siatki
 * @param solver instancja solver'a rozwiązującego równanie.
 * */
void LaasonenSolver::solveRow(int row, GausSeidelEquationSolver& solver)
{
    int rows = (int) mesh.getXPointsNum();
    for(int i = 0; i < rows; i++)
    {
        data.set(i, 0, -data.get(i, 0));
    }

    data.set(0, 0,  0.0);
    data.set(data.rows() - 1, 0,  0.0);

    solver.setTOLX(1e-7);
    solver.setCheckPeriod(100);
    solver.next(1000);
}

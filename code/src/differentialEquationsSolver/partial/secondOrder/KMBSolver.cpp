#include <iostream>
#include <fstream>
#include <chrono>
#include "differentialEquationsSolver/partial/secondOrder/KMBSolver.h"
#include "utils/Utils.h"


KMBSolver::KMBSolver(
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
        data(2, int (hInterval.size() / deltaH + 1))
{

}

/**
 * Funkcja oblicza wartości w danym wierszu siatki. Wynik zapisuje do pierwszego wiersza Macierzy data.
 *
 * @param row wiersz siatki
 * */
void KMBSolver::solveRow(int row)
{
    //Inicjalizacja, korzystając z wwarunków brzegowych
    data.set(1, 0,  lCond(mesh.getY(row - 1)));
    data.set(1, data.cols() - 1,  rCond(mesh.getY(row - 1)));

    //Rozwiązywanie równania w danym wierszu i zapisa wyniku do Macierzy
    double value;
    int cols = data.cols();
    for(int i = 1; i < cols - 1; i++)
    {
        value = lambda * data.get(0, i - 1);
        value += (1.0 - 2.0 * lambda) * data.get(0, i);
        value += lambda * data.get(0, i + 1);
        data.set(1, i, value);

    }
}


void KMBSolver::solve(bool appendResultToFile, std::string path = "")
{
    //save przechowuje ilość zapisów do pliku, jakie wykonałą funkcja solve
    static int save = 0;

    //rozpoczęcie odmierzania czasu
    auto start = std::chrono::steady_clock::now();

    //inicjalizacja, przy pomocy warunku początkowego
    for(int i = 0; i < data.cols(); i++)
        data.set(0, i, bottomCond(mesh.getX(i)));

    //iteracja po wierszach siatki
    int levels = (int) mesh.getYPointsNum();
    for(int t = 1; t < levels; t++)
    {
        //wyliczanie następnego wiersza i zapis wyniku do pierwszego wiersza macierzy "data".
        solveRow(t);
        //wynik z wiersza 1-szego macierzy zapisujemy do wiersza nr 0. Na podstawie
        //wiersza nr 0, w następnej iteracji, obliczamy wartość kolejnego wiersza.
        //Nie trzymamy w pamięci każdego obliczonego wiersza. Jest to konieczna optymalizacja pamięci.
        data.swapRows(0, 1);
    }

    //koniec odmierzania czasu
    auto end = std::chrono::steady_clock::now();

    //zapis daanych do pliku
    if(appendResultToFile)
    {
        std::ofstream file(path, std::ios::app);

        std::cout<<"zapis "<<save++<<std::endl;

        double maxAbsoluteError = 0;
        double t = mesh.getY(levels - 1);

        for(int i = 0; i < data.cols(); i++)
        {
            double tmp;
            double x = mesh.getX(i);
            tmp = std::abs(Utils::perfectSolution(x, t) - data.get(0, i));
        if(tmp > maxAbsoluteError)
                maxAbsoluteError = tmp;
        }
        file<<"lamda = "<<lambda<<" t = "<<t<<" delta h = "<<mesh.getDeltaX()<<" BBW = "<<maxAbsoluteError
            << " obliczenia zajely = "<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<<" sec\n";


         file.close();
    }
}


Matrix& KMBSolver::getSolution()
{
    return data;
}
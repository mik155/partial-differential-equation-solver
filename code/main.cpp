#include <cmath>
#include "differentialEquationsSolver/partial/secondOrder/KMBSolver.h"
#include "differentialEquationsSolver/partial/secondOrder/LaasonenSolver.h"

/**
 * lewy warunek berzegowy równania
 *
 * @param t argument funkcji
 *
 * @result zwraca wartość zadanej funkcji
 * */
double leftCondition(double t);

/**
 * prawy warunek berzegowy równania
 *
 * @param t argument funkcji
 *
 * @result zwraca wartość zadanej funkcji
 * */
double rightCondition(double t);

/**
* Warunek początkowy równania
 *
 * @param x argument funkcji
 *
 * @result zwraca wartość zadanej funkcji
 * */
double bottomCondition(double x);

/**
 * Rozwiązuje równanie, za pomocą 3 metod, dla zadanych parametrów.
 * Korzysta z metod : KMB, LAASONEN + THOMAS, LAASONEN + GAUSS-SEIDEL
 *
 * @param KMB_deltaT odległość pomiędzy węzłami siatki w pionie dla metody KMB
 * @param KMB_deltaH odległość pomiędzy węzłami siatki w poziomie dla metody KMB
 * @param LAA_deltaT odległość pomiędzy węzłami siatki w pionie dla metody LAASONEN
 * @param LAA_deltaH odległość pomiędzy węzłami siatki w poziomie  dla metody LAASONEN
 * */
void calculate(double KMB_deltaT, double KMB_deltaH, double LAA_deltaT, double LAA_deltaH);

/**
* Oblicza odległość pomiędzy węzłami w pionie, korzystając z zadanej odległości w poziomie.
 *Zapewnia, że lambda = 0.4.
 *
 * @param h odległość w poziomie pomiędzy węzłami w siatce jednorodnej
 *
 * @result zwraca odległość, w pionie, pomiędzy węzłami siatki
 * */
double calculateDeltaT_KMB(double h);

/**
* Oblicza odległość pomiędzy węzłami w pionie, korzystając z zadanej odległości w poziomie.
 *Zapewnia, że lambda = 1
 *
 * @param h odległość w poziomie pomiędzy węzłami w siatce jednorodnej
 *
 * @result zwraca odległość, w pionie, pomiędzy węzłami siatki
 * */
double calculateDeltaT_LGS(double h);


int main()
{
    //Definicja odległości  pomiędzy węzłami w poziomie, dla siatki jednorodnej
    double deltaH = 0.5;

    //Iteracja po odległości, w poziomie, pomiędzy węzłami
    while(deltaH > 1e-20)
    {
        //rozwiązujemy równanie i zapisujemy dane do pliku
        calculate(calculateDeltaT_KMB(deltaH), deltaH, calculateDeltaT_LGS(deltaH), deltaH);
        //zmniejszamy odległość pomiędzy węzłami
        deltaH /= 2.0;
    }

    return 0;
}

double calculateDeltaT_KMB(double h)
{
    return 0.4 * h * h;
}

double calculateDeltaT_LGS(double h)
{
    return h * h;
}

void calculate(double KMB_deltaT, double KMB_deltaH, double LAA_deltaT, double LAA_deltaH)
{
    //Definiiujemy przedziały, w których rozwiązujemy równanie.
    ClosedInterval hInterval(0.0, 1.0);
    ClosedInterval tInterval(0.0, 0.5);

    //Inicjaliozacja klas rozwiązujących równanie.
    KMBSolver solver0(hInterval, KMB_deltaH, tInterval, KMB_deltaT, 1.0, leftCondition, rightCondition, bottomCondition);
    LaasonenSolver solver1(hInterval, LAA_deltaH, tInterval, LAA_deltaT, 1.0, leftCondition, rightCondition, bottomCondition);

    //rozwiązywanie równania różniczkowego i zapis wyników do pliku
    solver0.solve(true, "OUTPUT\\KMB_BBW_TEST.txt");
    solver1.solveUsingThomasAlgorithm(true, "OUTPUT\\LAASONEN_THOMAS_TEST.txt");
    solver1.solveUsingGaussSeidelAlgorithm(true, "OUTPUT\\LAASONEN_GAUSS_SEIDEL_TEST.txt");
}

double leftCondition(double t)
{
    return 0;
}

double bottomCondition(double x)
{
    return sin(M_PI * x);
}

double rightCondition(double t)
{
    return 0;
}

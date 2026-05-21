#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-4; // точность вычислений 0.0001
const int MAX_ITER = 100; // максимальное количество итераций

// исходная функция f(x) = 2ln(x) - 0.5x + 1
double f(double x){
    return 2 * log(x) - 0.5 * x + 1;
}

// производная исходной для метода Ньютона
double df(double x){
    return 2.0 / x - 0.5;
}

// функция Ф(x) для метода простых итераций, Ф(x) = 4ln(x) + 2
double phi(double x){
    return 4 * log(x) + 2;
}

// метод половинного деления
void bisection(double a, double b){

    cout << "\n=== Метод половинного деления ===\n";

    cout << setw(5)  << "n"
         << setw(15) << "a"
         << setw(15) << "b"
         << setw(15) << "b-a"
         << endl;
    int n = 0;

    while ((b - a) > EPS && n < MAX_ITER){

        double c = (a + b) / 2.0; // середина текущего отрезка

        cout << setw(5)  << n // вывод строки таблицы
             << setw(15) << a
             << setw(15) << b
             << setw(15) << (b - a)
             << endl;
        if (f(a) * f(c) <= 0){ // смена знака, значит корень лежит между a и c
            b = c;
        }
        else{
            a = c;
        }
        n++;
    }
    double root = (a + b) / 2.0; //Приближённый корень = середина последнего отрезка

    cout << "Корень: " << root << endl;
    cout << "Итераций: " << n << endl;
}

//метод Ньютона, ищет касательную к графику, формула: x(n+1) = x(n) - f(x)/f'(x)
void newton(double x0){

    cout << "\n=== Метод Ньютона, x - f(x) / df(x) ===\n";

    cout << setw(5)  << "n"
         << setw(15) << "x_n"
         << setw(15) << "x_n+1"
         << setw(15) << "|dx|"
         << endl;

    double x = x0; // x = текущее приближение
    int n = 0;
    double delta; // разница между приближениями

    do{
        double x_new = x - f(x) / df(x); // формула Ньютона
        delta = fabs(x_new - x);

        cout << setw(5)  << n
             << setw(15) << x
             << setw(15) << x_new
             << setw(15) << delta
             << endl;
        x = x_new; // след приблежение
        n++;

    } while (delta > EPS && n < MAX_ITER);
    cout << "Корень: " << x << endl;
    cout << "Итераций: " << n << endl;
}


//метод простых итераций, формула: x(n+1) = Ф(x(n)), моя: Ф(x) = 4ln(x) + 2
void simple_iteration(double x0){

    cout << "\n=== Метод простых итераций, x(n+1) = Ф(x(n)), Ф(x) = 4ln(x) + 2 ===\n";

    cout << setw(5)  << "n"
         << setw(15) << "x_n"
         << setw(15) << "x_n+1"
         << setw(15) << "|dx|"
         << endl;

    double x = x0; // Начальное приближение
    int n = 0;
    double delta;

    do{
        double x_new = phi(x); // новое приближение
        delta = fabs(x_new - x);

        cout << setw(5)  << n
             << setw(15) << x
             << setw(15) << x_new
             << setw(15) << delta
             << endl;

        x = x_new; //обновляем x
        n++;

    } while (delta > EPS && n < MAX_ITER);
    cout << "Корень: " << x << endl;
    cout << "Итераций: " << n << endl;
}

int main(){

    cout << fixed << setprecision(6); // точность 6 цифр после запятой

    //1) f(0.5) < 0, f(1) > 0, значит корень есть на [0.5 ; 1]
    cout << "Первый корень [0.5 ; 1]\n";

    bisection(0.5, 1.0);// Метод половинного деления
    newton(0.8); // Для Ньютона и итераций задаём начальное приближение
    simple_iteration(0.8);

    //2) f(10) > 0, f(12) < 0, значит корень на [10 ; 12]
    cout << "\n\nВторой корень [10 ; 12]\n";

    bisection(10.0, 12.0);
    newton(11.0);// начальное приближение
    simple_iteration(11.0);
    return 0;
}

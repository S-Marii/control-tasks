#include <iostream>
#include <windows.h>
#include <cmath>
#include <tuple>
#include <complex>

using namespace std;

// Псевдоним для кортежа с решением
using SolutionTuple = tuple<double, double, bool>;

// Функция решения квадратного уравнения (возвращает кортеж)
SolutionTuple solveQuadraticTuple(double a, double b, double c) {
    if (a == 0) {
        // Линейное уравнение
        if (b == 0) {
            return make_tuple(0.0, 0.0, false);
        }
        double root = -c / b;
        return make_tuple(root, root, true);
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return make_tuple(0.0, 0.0, false);
    }

    double sqrtD = sqrt(discriminant);
    double root1 = (-b + sqrtD) / (2 * a);
    double root2 = (-b - sqrtD) / (2 * a);

    return make_tuple(root1, root2, true);
}

// Функция для вывода кортежа с решением
void printSolution(const SolutionTuple& solution) {
    double root1 = get<0>(solution);
    double root2 = get<1>(solution);
    bool hasRoots = get<2>(solution);

    cout << "Кортеж решения: ("
        << root1 << ", " << root2 << ", "
        << (hasRoots ? "true" : "false") << ")\n";

    if (!hasRoots) {
        cout << "Действительных корней нет\n";
    }
    else if (root1 == root2) {
        cout << "Один корень: x = " << root1 << endl;
    }
    else {
        cout << "Два корня: x1 = " << root1 << ", x2 = " << root2 << endl;
    }
}

// Дополнительная функция: решение с комплексными корнями
using ComplexSolution = tuple<complex<double>, complex<double>, bool>;

ComplexSolution solveQuadraticComplex(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) {
            return make_tuple(complex<double>(0), complex<double>(0), false);
        }
        complex<double> root(-c / b, 0);
        return make_tuple(root, root, true);
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double sqrtD = sqrt(discriminant);
        double root1 = (-b + sqrtD) / (2 * a);
        double root2 = (-b - sqrtD) / (2 * a);
        return make_tuple(complex<double>(root1, 0), complex<double>(root2, 0), true);
    }
    else {
        double sqrtD = sqrt(-discriminant);
        complex<double> root1(-b / (2 * a), sqrtD / (2 * a));
        complex<double> root2(-b / (2 * a), -sqrtD / (2 * a));
        return make_tuple(root1, root2, true);
    }
}

// Функция для вывода комплексного решения
void printComplexSolution(const ComplexSolution& solution) {
    auto root1 = get<0>(solution);
    auto root2 = get<1>(solution);
    bool hasRoots = get<2>(solution);

    cout << "Комплексное решение:\n";
    if (hasRoots) {
        cout << "x1 = " << root1 << "\n";
        cout << "x2 = " << root2 << "\n";
    }
    else {
        cout << "Корней нет\n";
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "=== Решение квадратного уравнения (кортеж) ===\n";

    double a, b, c;

    cout << "Введите коэффициенты квадратного уравнения ax² + bx + c = 0:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;

    // Решение с использованием кортежа
    SolutionTuple solution = solveQuadraticTuple(a, b, c);

    cout << "\nРешение уравнения " << a << "x² + " << b << "x + " << c << " = 0:\n";
    printSolution(solution);

    // Демонстрация работы с комплексными числами
    cout << "\n=== Решение с комплексными корнями ===\n";
    ComplexSolution complexSolution = solveQuadraticComplex(a, b, c);
    printComplexSolution(complexSolution);

    return 0;
}
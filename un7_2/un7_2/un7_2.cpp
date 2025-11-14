#include <iostream>
#include <windows.h>
#include <cmath>
#include <tuple>

using namespace std;

// Структура для решения квадратного уравнения
struct QuadraticSolution {
    double root1;
    double root2;
    bool hasRealRoots;

    // Конструктор
    QuadraticSolution(double r1 = 0, double r2 = 0, bool hasRoots = false)
        : root1(r1), root2(r2), hasRealRoots(hasRoots) {
    }

    // Функция для вывода решения
    void show() const {
        if (!hasRealRoots) {
            cout << "Действительных корней нет\n";
        }
        else if (root1 == root2) {
            cout << "Один корень: x = " << root1 << endl;
        }
        else {
            cout << "Два корня: x1 = " << root1 << ", x2 = " << root2 << endl;
        }
    }
};

// Функция решения квадратного уравнения (возвращает структуру)
QuadraticSolution solveQuadratic(double a, double b, double c) {
    if (a == 0) {
        // Линейное уравнение
        if (b == 0) {
            return QuadraticSolution(0, 0, false);
        }
        double root = -c / b;
        return QuadraticSolution(root, root, true);
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return QuadraticSolution(0, 0, false);
    }

    double sqrtD = sqrt(discriminant);
    double root1 = (-b + sqrtD) / (2 * a);
    double root2 = (-b - sqrtD) / (2 * a);

    return QuadraticSolution(root1, root2, true);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "=== Решение квадратного уравнения (структура) ===\n";

    double a, b, c;

    cout << "Введите коэффициенты квадратного уравнения ax² + bx + c = 0:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;

    QuadraticSolution solution = solveQuadratic(a, b, c);

    cout << "\nРешение уравнения " << a << "x² + " << b << "x + " << c << " = 0:\n";
    solution.show();

    return 0;
}
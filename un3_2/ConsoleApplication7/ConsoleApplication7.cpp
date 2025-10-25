#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double cubeRootPow(double a) {
    if (a < 0) {
        return -pow(-a, 1.0 / 3.0);
    }
    return pow(a, 1.0 / 3.0);
}

double cubeRootIterative(double a, double epsilon = 1e-10) {
    if (a == 0) return 0;

    double x = a; 
    double prev;

    do {
        prev = x;
        x = (2 * x + a / (x * x)) / 3;
    } while (abs(x - prev) > epsilon);

    return x;
}

double cubeRootIterative(double a, int maxIterations) {
    if (a == 0) return 0;

    double x = a;
    for (int i = 0; i < maxIterations; i++) {
        x = (2 * x + a / (x * x)) / 3;
    }
    return x;
}

int main() {
    system("chcp 1251");

    cout << "=== ВЫЧИСЛЕНИЕ КУБИЧЕСКОГО КОРНЯ ===\n\n";

    double number;
    cout << "Введите число для вычисления кубического корня: ";
    cin >> number;

    cout << fixed << setprecision(10);
    cout << "\nРезультаты вычислений:\n";
    cout << "Метод pow():        " << cubeRootPow(number) << endl;
    cout << "Итерационный метод: " << cubeRootIterative(number) << endl;
    cout << "Итерационный (10 итераций): " << cubeRootIterative(number, 10) << endl;
    cout << "Проверка (result³): " << pow(cubeRootIterative(number), 3) << endl;
        
    cout << "\nТестирование на различных значениях:\n";
    double testValues[] = { 8, 27, 64, 1000, -8, -27, 0.125 };

    for (double val : testValues) {
        cout << "\nЧисло: " << val << endl;
        cout << "pow(): " << cubeRootPow(val) << ", итерац.: " << cubeRootIterative(val);
        cout << ", разница: " << abs(cubeRootPow(val) - cubeRootIterative(val)) << endl;
    }

    return 0;
}
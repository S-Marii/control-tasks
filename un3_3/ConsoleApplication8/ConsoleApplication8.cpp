#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double triangleArea(double side) {
    return (sqrt(3) / 4) * side * side;
}

double triangleArea(double a, double b, double c) {
    double p = (a + b + c) / 2; // полупериметр
    return sqrt(p * (p - a) * (p - b) * (p - c)); // формула Герона
}

void printTriangleArea(double side) {
    double area = triangleArea(side);
    cout << "Равносторонний треугольник со стороной " << side << endl;
    cout << "Площадь: " << fixed << setprecision(4) << area << endl;
}

void printTriangleArea(double a, double b, double c) {
    double area = triangleArea(a, b, c);
    cout << "Разносторонний треугольник со сторонами "
        << a << ", " << b << ", " << c << endl;
    cout << "Площадь: " << fixed << setprecision(4) << area << endl;
}

int main() {
    system("chcp 1251");

    cout << "=== ВЫЧИСЛЕНИЕ ПЛОЩАДИ ТРЕУГОЛЬНИКОВ ===\n\n";

    char choice;
    cout << "Выберите тип треугольника:\n";
    cout << "1 - Равносторонний\n";
    cout << "2 - Разносторонний\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
    case '1': {
        double side;
        cout << "Введите длину стороны: ";
        cin >> side;
        printTriangleArea(side);
        break;
    }
    case '2': {
        double a, b, c;
        cout << "Введите три стороны треугольника: ";
        cin >> a >> b >> c;
                
        if (a + b > c && a + c > b && b + c > a) {
            printTriangleArea(a, b, c);
        }
        else {
            cout << "Треугольник с такими сторонами не существует!" << endl;
        }
        break;
    }
    default:
        cout << "Неверный выбор!" << endl;
    }
        
    cout << "\nДемонстрация перегрузки функций:\n";
    printTriangleArea(5.0);           
    printTriangleArea(3.0, 4.0, 5.0); 

    return 0;
}
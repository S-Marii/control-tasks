#include "triangle.h"
#include <cmath>
#include <iomanip>

using namespace std;

// Конструктор равносторонний треугольник со стороной 1
Triangle::Triangle() : sideA_(1.0), sideB_(1.0), sideC_(1.0) {
    cout << "Создан треугольник по умолчанию: ";
    display();
}

// Конструктор с параметрами
Triangle::Triangle(double a, double b, double c) {
    validateSides(a, b, c);
    sideA_ = a;
    sideB_ = b;
    sideC_ = c;
    cout << "Создан треугольник: ";
    display();
}

// Проверка корректности сторон треугольника
void Triangle::validateSides(double a, double b, double c) const {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw InvalidTriangleError("Все стороны треугольника должны быть положительными", a, b, c);
    }

    if (a + b <= c || a + c <= b || b + c <= a) {
        throw InvalidTriangleError("Нарушено неравенство треугольника: сумма двух сторон должна быть больше третьей", a, b, c);
    }
}

// Статическая проверка треугольника
bool Triangle::isValidTriangle(double a, double b, double c) {
    return (a > 0 && b > 0 && c > 0) &&
        (a + b > c) && (a + c > b) && (b + c > a);
}

// Проверка текущего треугольника
bool Triangle::isValidTriangle() const {
    return isValidTriangle(sideA_, sideB_, sideC_);
}

// Установка стороны A
void Triangle::setSideA(double a) {
    validateSides(a, sideB_, sideC_);
    sideA_ = a;
    cout << "Установлена сторона A = " << a << endl;
}

// Установка стороны B
void Triangle::setSideB(double b) {
    validateSides(sideA_, b, sideC_);
    sideB_ = b;
    cout << "Установлена сторона B = " << b << endl;
}

// Установка стороны C
void Triangle::setSideC(double c) {
    validateSides(sideA_, sideB_, c);
    sideC_ = c;
    cout << "Установлена сторона C = " << c << endl;
}

// Установка всех сторон
void Triangle::setSides(double a, double b, double c) {
    validateSides(a, b, c);
    sideA_ = a;
    sideB_ = b;
    sideC_ = c;
    cout << "Установлены все стороны: ";
    display();
}

// Вычисление площади по формуле Герона
double Triangle::calculateArea() const {
    if (!isValidTriangle()) {
        throw InvalidTriangleError("Невозможно вычислить площадь для недопустимого треугольника",
            sideA_, sideB_, sideC_);
    }

    double p = calculatePerimeter() / 2.0;
    return sqrt(p * (p - sideA_) * (p - sideB_) * (p - sideC_));
}

// Вычисление периметра
double Triangle::calculatePerimeter() const {
    return sideA_ + sideB_ + sideC_;
}

// Вывод информации о треугольнике
void Triangle::display() const {
    cout << fixed << setprecision(2);
    cout << "Треугольник [" << sideA_ << ", " << sideB_ << ", " << sideC_ << "]";
    if (isValidTriangle()) {
        cout << " Периметр: " << calculatePerimeter()
            << " Площадь: " << calculateArea();
    }
    else {
        cout << " (недопустимый)";
    }
    cout << endl;
}
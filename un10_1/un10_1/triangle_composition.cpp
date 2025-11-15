#include "triangle_composition.h"
#include <iomanip>
#include <stdexcept>

using namespace std;

// Конструктор по умолчанию (равнобедренный треугольник)
TriangleComposition::TriangleComposition()
    : vertexA(0, 0), vertexB(1, 0), vertexC(0.5, sqrt(3) / 2) {
    cout << "Создан треугольник по умолчанию (композиция)" << endl;
    displayInfo();
}

// Конструктор с координатами
TriangleComposition::TriangleComposition(double x1, double y1, double x2, double y2, double x3, double y3)
    : vertexA(x1, y1), vertexB(x2, y2), vertexC(x3, y3) {
    if (!isValidTriangle()) {
        throw invalid_argument("Точки не образуют треугольник");
    }
    cout << "Создан треугольник по координатам (композиция)" << endl;
    displayInfo();
}

// Конструктор с объектами точек
TriangleComposition::TriangleComposition(const Dot& a, const Dot& b, const Dot& c)
    : vertexA(a), vertexB(b), vertexC(c) {
    if (!isValidTriangle()) {
        throw invalid_argument("Точки не образуют треугольник");
    }
    cout << "Создан треугольник из точек (композиция)" << endl;
    displayInfo();
}

// Деструктор
TriangleComposition::~TriangleComposition() {
    cout << "Уничтожен треугольник (композиция)" << endl;
}

// Длина стороны AB
double TriangleComposition::getSideAB() const {
    return vertexA.distanceTo(vertexB);
}

// Длина стороны BC
double TriangleComposition::getSideBC() const {
    return vertexB.distanceTo(vertexC);
}

// Длина стороны CA
double TriangleComposition::getSideCA() const {
    return vertexC.distanceTo(vertexA);
}

// Периметр треугольника
double TriangleComposition::calculatePerimeter() const {
    return getSideAB() + getSideBC() + getSideCA();
}

// Площадь треугольника по формуле Герона
double TriangleComposition::calculateArea() const {
    if (!isValidTriangle()) {
        return 0.0;
    }

    double a = getSideAB();
    double b = getSideBC();
    double c = getSideCA();
    double p = calculatePerimeter() / 2.0;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// Проверка, образуют ли точки треугольник
bool TriangleComposition::isValidTriangle() const {
    double a = getSideAB();
    double b = getSideBC();
    double c = getSideCA();

    return (a + b > c) && (a + c > b) && (b + c > a) &&
        (a > 0) && (b > 0) && (c > 0);
}

// Вывод длин сторон
void TriangleComposition::displaySides() const {
    cout << fixed << setprecision(2);
    cout << "Длины сторон треугольника:" << endl;
    cout << "AB = " << getSideAB() << endl;
    cout << "BC = " << getSideBC() << endl;
    cout << "CA = " << getSideCA() << endl;
}

// Вывод полной информации о треугольнике
void TriangleComposition::displayInfo() const {
    cout << fixed << setprecision(2);
    cout << "=== Информация о треугольнике (композиция) ===" << endl;
    vertexA.display("Вершина A");
    vertexB.display("Вершина B");
    vertexC.display("Вершина C");
    displaySides();
    cout << "Периметр: " << calculatePerimeter() << endl;
    cout << "Площадь: " << calculateArea() << endl;
    cout << "Является треугольником: " << (isValidTriangle() ? "Да" : "Нет") << endl;
    cout << "=============================================" << endl;
}
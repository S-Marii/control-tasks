#include "triangle_aggregation.h"
#include <iomanip>
#include <stdexcept>

using namespace std;

// Конструктор по умолчанию (нулевые указатели)
TriangleAggregation::TriangleAggregation()
    : vertexA(nullptr), vertexB(nullptr), vertexC(nullptr) {
    cout << "Создан треугольник по умолчанию (агрегация) - вершины не установлены" << endl;
}

// Конструктор с указателями на точки
TriangleAggregation::TriangleAggregation(const Dot* a, const Dot* b, const Dot* c)
    : vertexA(a), vertexB(b), vertexC(c) {
    if (!vertexA || !vertexB || !vertexC) {
        throw invalid_argument("Все вершины должны быть установлены");
    }
    if (!isValidTriangle()) {
        throw invalid_argument("Точки не образуют треугольник");
    }
    cout << "Создан треугольник из указателей на точки (агрегация)" << endl;
    displayInfo();
}

// Деструктор
TriangleAggregation::~TriangleAggregation() {
    cout << "Уничтожен треугольник (агрегация)" << endl;    
}

// Длина стороны AB
double TriangleAggregation::getSideAB() const {
    if (!vertexA || !vertexB) return 0.0;
    return vertexA->distanceTo(*vertexB);
}

// Длина стороны BC
double TriangleAggregation::getSideBC() const {
    if (!vertexB || !vertexC) return 0.0;
    return vertexB->distanceTo(*vertexC);
}

// Длина стороны CA
double TriangleAggregation::getSideCA() const {
    if (!vertexC || !vertexA) return 0.0;
    return vertexC->distanceTo(*vertexA);
}

// Периметр треугольника
double TriangleAggregation::calculatePerimeter() const {
    return getSideAB() + getSideBC() + getSideCA();
}

// Площадь треугольника по формуле Герона
double TriangleAggregation::calculateArea() const {
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
bool TriangleAggregation::isValidTriangle() const {
    if (!vertexA || !vertexB || !vertexC) {
        return false;
    }

    double a = getSideAB();
    double b = getSideBC();
    double c = getSideCA();

    return (a + b > c) && (a + c > b) && (b + c > a) &&
        (a > 0) && (b > 0) && (c > 0);
}

// Вывод длин сторон
void TriangleAggregation::displaySides() const {
    if (!vertexA || !vertexB || !vertexC) {
        cout << "Вершины треугольника не установлены" << endl;
        return;
    }

    cout << fixed << setprecision(2);
    cout << "Длины сторон треугольника:" << endl;
    cout << "AB = " << getSideAB() << endl;
    cout << "BC = " << getSideBC() << endl;
    cout << "CA = " << getSideCA() << endl;
}

// Вывод полной информации о треугольнике
void TriangleAggregation::displayInfo() const {
    if (!vertexA || !vertexB || !vertexC) {
        cout << "Треугольник не полностью инициализирован" << endl;
        return;
    }

    cout << fixed << setprecision(2);
    cout << "=== Информация о треугольнике (агрегация) ===" << endl;
    vertexA->display("Вершина A");
    vertexB->display("Вершина B");
    vertexC->display("Вершина C");
    displaySides();
    cout << "Периметр: " << calculatePerimeter() << endl;
    cout << "Площадь: " << calculateArea() << endl;
    cout << "Является треугольником: " << (isValidTriangle() ? "Да" : "Нет") << endl;
    cout << "============================================" << endl;
}
#include "dot.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Конструктор по умолчанию
Dot::Dot() : x(0), y(0) {
    cout << "Создана точка по умолчанию: ";
    display();
}

// Конструктор с параметрами
Dot::Dot(double x, double y) : x(x), y(y) {
    cout << "Создана точка: ";
    display();
}

// Деструктор
Dot::~Dot() {
    cout << "Уничтожена точка: ";
    display();
}

// Вычисление расстояния до другой точки
double Dot::distanceTo(const Dot& point) const {
    return sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
}

// Вывод координат точки
void Dot::display() const {
    cout << fixed << setprecision(2);
    cout << "(" << x << ", " << y << ")" << endl;
}

// Вывод координат точки с меткой
void Dot::display(const std::string& label) const {
    cout << label << ": ";
    display();
}
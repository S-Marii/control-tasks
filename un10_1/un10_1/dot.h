#pragma once
#include <cmath>
#include <string>
#include <iostream>

class Dot {
private:
    double x;
    double y;

public:
    // Конструкторы
    Dot();
    Dot(double x, double y);

    // Методы доступа
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    // Основные методы
    double distanceTo(const Dot& point) const;
    void display() const;
    void display(const std::string& label) const;
    // Деструктор
    ~Dot();
};
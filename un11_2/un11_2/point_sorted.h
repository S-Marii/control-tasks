#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class Point {
private:
    double x;
    double y;

public:
    // Конструкторы
    Point();
    Point(double x, double y);

    // Методы доступа
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    // Основные методы
    double distanceToOrigin() const;
    void display() const;

    // Перегрузка операторов сравнения для сортировки
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
    bool operator<=(const Point& other) const;
    bool operator>=(const Point& other) const;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Point& point);

    // Деструктор
    ~Point();
};
#pragma once
#include "dot.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

class TriangleComposition {
private:    
    Dot vertexA;
    Dot vertexB;
    Dot vertexC;

public:
    // Конструкторы
    TriangleComposition();
    TriangleComposition(double x1, double y1, double x2, double y2, double x3, double y3);
    TriangleComposition(const Dot& a, const Dot& b, const Dot& c);

    // Методы доступа к вершинам
    Dot getVertexA() const { return vertexA; }
    Dot getVertexB() const { return vertexB; }
    Dot getVertexC() const { return vertexC; }

    // Основные методы
    double getSideAB() const;
    double getSideBC() const;
    double getSideCA() const;
    double calculatePerimeter() const;
    double calculateArea() const;
    bool isValidTriangle() const;
    void displaySides() const;
    void displayInfo() const;

    // Деструктор
    ~TriangleComposition();
};
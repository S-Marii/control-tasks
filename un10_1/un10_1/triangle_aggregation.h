#pragma once
#include "dot.h"
#include <iostream>
#include <string>
#include <cmath>
#include <memory>

class TriangleAggregation {
private:    
    const Dot* vertexA;
    const Dot* vertexB;
    const Dot* vertexC;

public:
    // Конструкторы
    TriangleAggregation();
    TriangleAggregation(const Dot* a, const Dot* b, const Dot* c);

    // Методы доступа к вершинам
    const Dot* getVertexA() const { return vertexA; }
    const Dot* getVertexB() const { return vertexB; }
    const Dot* getVertexC() const { return vertexC; }
    void setVertexA(const Dot* a) { vertexA = a; }
    void setVertexB(const Dot* b) { vertexB = b; }
    void setVertexC(const Dot* c) { vertexC = c; }

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
    ~TriangleAggregation();
};
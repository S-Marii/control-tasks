#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

class Triangle {
public:
    // Класс исключения для недопустимых сторон треугольника
    class InvalidTriangleError : public std::exception {
    public:
        InvalidTriangleError(const std::string& message, double a, double b, double c)
            : message_(message), sideA_(a), sideB_(b), sideC_(c) {
        }

        const char* what() const noexcept override {
            return message_.c_str();
        }

        void printDetails() const {
            std::cout << "Ошибка треугольника: " << message_ << std::endl;
            std::cout << "Стороны: a=" << sideA_ << ", b=" << sideB_ << ", c=" << sideC_ << std::endl;
        }

        double getSideA() const { return sideA_; }
        double getSideB() const { return sideB_; }
        double getSideC() const { return sideC_; }

    private:
        std::string message_;
        double sideA_, sideB_, sideC_;
    };

    // Конструкторы
    Triangle();
    Triangle(double a, double b, double c);

    // Методы доступа
    double getSideA() const { return sideA_; }
    double getSideB() const { return sideB_; }
    double getSideC() const { return sideC_; }

    // Методы установки сторон с проверкой
    void setSideA(double a);
    void setSideB(double b);
    void setSideC(double c);
    void setSides(double a, double b, double c);

    // Основные методы
    double calculateArea() const;
    double calculatePerimeter() const;
    bool isValidTriangle() const;
    void display() const;

    // Статические методы
    static bool isValidTriangle(double a, double b, double c);

private:
    double sideA_, sideB_, sideC_;

    // Вспомогательные методы
    void validateSides(double a, double b, double c) const;
};
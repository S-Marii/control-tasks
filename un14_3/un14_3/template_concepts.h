#pragma once
#include <iostream>
#include <concepts>
#include <string>

// Концепт для типов, поддерживающих оператор <
template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

// Шаблонная функция maxOfTwo с ограничением Comparable
template<Comparable T>
const T& maxOfTwo(const T& a, const T& b) {
    return (a < b) ? b : a;
}

// Пользовательский класс для тестирования
class Product {
private:
    std::string name;
    double price;

public:
    Product(const std::string& n = "", double p = 0.0) : name(n), price(p) {}

    // Оператор < для сравнения по цене
    bool operator<(const Product& other) const {
        return price < other.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << p.name << " ($" << p.price << ")";
        return os;
    }

    // Методы доступа
    std::string getName() const { return name; }
    double getPrice() const { return price; }
};

// Класс без оператора < (для демонстрации ошибки компиляции)
class NonComparable {
private:
    int data;

public:
    NonComparable(int d = 0) : data(d) {}

    // Нет оператора <
};
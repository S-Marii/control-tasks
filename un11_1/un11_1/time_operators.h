#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    // Конструкторы
    Time();
    Time(int h, int m, int s);

    // Методы доступа
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    // Основные методы
    void normalize();
    int toSeconds() const;
    void fromSeconds(int totalSeconds);
    void display() const;

    // Перегрузка арифметических операторов
    Time operator+(const Time& other) const;
    Time operator-(const Time& other) const;
    Time operator+(double hoursToAdd) const;
    Time operator-(double hoursToSubtract) const;

    // Дружественные функции для операций с double слева
    friend Time operator+(double hoursToAdd, const Time& time);
    friend Time operator-(double hoursToSubtract, const Time& time);

    // Перегрузка операторов сравнения
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
    friend std::istream& operator>>(std::istream& is, Time& time);

    // Операторы присваивания
    Time& operator+=(const Time& other);
    Time& operator-=(const Time& other);

    // Преобразования типов
    operator double() const; // Преобразование Time в double (часы)
    operator int() const;    // Преобразование Time в int (секунды)

    // Деструктор
    ~Time();
};
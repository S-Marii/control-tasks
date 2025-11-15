#pragma once
#include <iostream>
#include <string>

class Time {
public:
    // Конструкторы
    Time();
    Time(int h, int m, int s);

    // Методы доступа
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    // Методы установки значений
    void setHours(int h);
    void setMinutes(int m);
    void setSeconds(int s);

    // Основные методы
    void display() const;
    void display(const std::string& label) const;
    Time add(const Time& other) const;
    Time subtract(const Time& other) const;

    // Вспомогательные методы
    int toSeconds() const;
    void normalize();

    // Деструктор
    ~Time();

private:
    int hours;
    int minutes;
    int seconds;
};
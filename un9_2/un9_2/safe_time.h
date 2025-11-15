#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class SafeTime {
public:
    // Классы исключений
    class InvalidTimeError : public std::exception {
    public:
        InvalidTimeError(const std::string& message, int h, int m, int s)
            : message_(message), hours_(h), minutes_(m), seconds_(s) {
        }

        const char* what() const noexcept override {
            return message_.c_str();
        }

        void printDetails() const {
            std::cout << "Ошибка времени: " << message_ << std::endl;
            std::cout << "Время: " << hours_ << ":" << minutes_ << ":" << seconds_ << std::endl;
        }

        int getHours() const { return hours_; }
        int getMinutes() const { return minutes_; }
        int getSeconds() const { return seconds_; }

    private:
        std::string message_;
        int hours_, minutes_, seconds_;
    };

    class TimeOperationError : public std::exception {
    public:
        TimeOperationError(const std::string& message, const std::string& operation)
            : message_(message), operation_(operation) {
        }

        const char* what() const noexcept override {
            return message_.c_str();
        }

        void printDetails() const {
            std::cout << "Ошибка операции: " << message_ << std::endl;
            std::cout << "Операция: " << operation_ << std::endl;
        }

    private:
        std::string message_;
        std::string operation_;
    };

    // Конструкторы
    SafeTime();
    SafeTime(int h, int m, int s);
    SafeTime(const SafeTime& other); // Конструктор копирования
    SafeTime(SafeTime&& other) noexcept; // Конструктор перемещения

    // Операторы присваивания
    SafeTime& operator=(const SafeTime& other);
    SafeTime& operator=(SafeTime&& other) noexcept;

    // Арифметические операторы
    SafeTime operator+(const SafeTime& other) const;
    SafeTime operator-(const SafeTime& other) const;
    SafeTime& operator+=(const SafeTime& other);
    SafeTime& operator-=(const SafeTime& other);

    // Операторы сравнения
    bool operator==(const SafeTime& other) const;
    bool operator!=(const SafeTime& other) const;
    bool operator<(const SafeTime& other) const;
    bool operator>(const SafeTime& other) const;

    // Методы доступа
    int getHours() const { return hours_; }
    int getMinutes() const { return minutes_; }
    int getSeconds() const { return seconds_; }

    // Методы установки значений с проверкой
    void setHours(int h);
    void setMinutes(int m);
    void setSeconds(int s);
    void setTime(int h, int m, int s);

    // Основные методы
    void display() const;
    void display(const std::string& label) const;
    int toSeconds() const;
    void fromSeconds(int totalSeconds);

    // Вспомогательные методы
    void normalize();
    bool isValidTime() const;
    static bool isValidTime(int h, int m, int s);

    // Деструктор
    ~SafeTime();

private:
    int hours_;
    int minutes_;
    int seconds_;

    // Вспомогательные методы
    void validateTime(int h, int m, int s) const;
    void validateNonNegative() const;
};  // <- ВАЖНО: точка с запятой после объявления класса
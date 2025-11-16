#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>
#include <string>

// Шаблонная функция для вычисления среднего арифметического массива
template<typename T>
auto calculateAverage(const T arr[], int size) -> decltype(arr[0] + arr[0]) {
    if (size <= 0) {
        // Возвращаем значение по умолчанию для типа
        return T{};
    }

    decltype(arr[0] + arr[0]) sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum / static_cast<decltype(sum)>(size);
}

// Шаблонная функция для вывода массива
template<typename T>
void printArray(const T arr[], int size, const std::string& delimiter = ", ") {
    if (size <= 0) {
        std::cout << "[]" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) {
            std::cout << delimiter;
        }
    }
    std::cout << std::endl;
}

// Специализация для char - выводим как строку
template<>
void printArray<char>(const char arr[], int size, const std::string& delimiter) {
    if (size <= 0) {
        std::cout << "[]" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
    }
    std::cout << std::endl;
}
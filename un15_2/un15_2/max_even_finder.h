#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <functional>
#include <climits>
#include <random>

class MaxEvenFinder {
public:
    // Основная функция поиска максимального четного числа
    static int FindMaxEven(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::runtime_error("Вектор пуст");
        }
                
        auto it = std::max_element(numbers.begin(), numbers.end(),
            [](int a, int b) {                
                bool a_even = (a % 2 == 0);
                bool b_even = (b % 2 == 0);
                
                if (a_even && b_even) {
                    return a < b;
                }
                
                else if (!a_even && !b_even) {
                    return false;
                }
                
                else {
                    return !a_even; // true если a нечетное (тогда a < b)
                }
            });

        // Проверяем
        if (*it % 2 != 0) {
            throw std::runtime_error("В векторе нет четных чисел");
        }

        return *it;
    }

    // Альтернативная реализация с использованием copy_if и max_element
    static int FindMaxEvenAlternative(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::runtime_error("Вектор пуст");
        }
                
        std::vector<int> evenNumbers;
        std::copy_if(numbers.begin(), numbers.end(),
            std::back_inserter(evenNumbers),
            [](int n) { return n % 2 == 0; });

        if (evenNumbers.empty()) {
            throw std::runtime_error("В векторе нет четных чисел");
        }
                
        return *std::max_element(evenNumbers.begin(), evenNumbers.end());
    }

    // Безопасная реализация с ручным поиском
    static int FindMaxEvenSafe(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::runtime_error("Вектор пуст");
        }

        int maxEven = INT_MIN;
        bool foundEven = false;

        for (int num : numbers) {
            if (num % 2 == 0) {
                if (!foundEven || num > maxEven) {
                    maxEven = num;
                    foundEven = true;
                }
            }
        }

        if (!foundEven) {
            throw std::runtime_error("В векторе нет четных чисел");
        }

        return maxEven;
    }

    // Функция для поиска всех четных чисел
    static std::vector<int> FindAllEven(const std::vector<int>& numbers) {
        std::vector<int> evenNumbers;
        std::copy_if(numbers.begin(), numbers.end(),
            std::back_inserter(evenNumbers),
            [](int n) { return n % 2 == 0; });
        return evenNumbers;
    }

    // Функция для поиска минимального четного числа
    static int FindMinEven(const std::vector<int>& numbers) {
        auto evenNumbers = FindAllEven(numbers);
        if (evenNumbers.empty()) {
            throw std::runtime_error("В векторе нет четных чисел");
        }
        return *std::min_element(evenNumbers.begin(), evenNumbers.end());
    }

    // Поиск максимального нечетного числа
    static int FindMaxOdd(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::runtime_error("Вектор пуст");
        }

        // Используем безопасный метод с copy_if
        std::vector<int> oddNumbers;
        std::copy_if(numbers.begin(), numbers.end(),
            std::back_inserter(oddNumbers),
            [](int n) { return n % 2 != 0; });

        if (oddNumbers.empty()) {
            throw std::runtime_error("В векторе нет нечетных чисел");
        }

        return *std::max_element(oddNumbers.begin(), oddNumbers.end());
    }

    // Статистика по вектору
    static void PrintVectorStats(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            std::cout << "Вектор пуст." << std::endl;
            return;
        }

        auto evenNumbers = FindAllEven(numbers);
        auto oddNumbersCount = numbers.size() - evenNumbers.size();

        std::cout << "Общее количество чисел: " << numbers.size() << std::endl;
        std::cout << "Четных чисел: " << evenNumbers.size() << std::endl;
        std::cout << "Нечетных чисел: " << oddNumbersCount << std::endl;

        try {
            if (!evenNumbers.empty()) {
                std::cout << "Максимальное четное: " << FindMaxEvenSafe(numbers) << std::endl;
                std::cout << "Минимальное четное: " << FindMinEven(numbers) << std::endl;
            }
            else {
                std::cout << "Четных чисел нет" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при поиске четных чисел: " << e.what() << std::endl;
        }

        try {
            if (oddNumbersCount > 0) {
                std::cout << "Максимальное нечетное: " << FindMaxOdd(numbers) << std::endl;
            }
            else {
                std::cout << "Нечетных чисел нет" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при поиске нечетных чисел: " << e.what() << std::endl;
        }
    }

    // Генерация случайного вектора
    static std::vector<int> GenerateRandomVector(size_t size, int minVal = 1, int maxVal = 1000) {
        std::vector<int> result;
        result.reserve(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(minVal, maxVal);

        for (size_t i = 0; i < size; ++i) {
            result.push_back(dis(gen));
        }

        return result;
    }
};
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include "max_even_finder.h"

using namespace std;

void demonstrateMaxEvenFinding() {
    cout << "=== ПОИСК МАКСИМАЛЬНОГО ЧЁТНОГО ЧИСЛА В ВЕКТОРЕ ===\n" << endl;

    // 1. Тест с обычным вектором
    cout << "1. Обычный вектор:" << endl;
    cout << "=================" << endl;

    vector<int> numbers1 = { 1, 3, 8, 2, 7, 12, 5, 6, 9, 4 };
    cout << "Вектор: ";
    for (int n : numbers1) cout << n << " ";
    cout << endl;

    try {
        cout << "Метод 1 (с компаратором): ";
        int maxEven1 = MaxEvenFinder::FindMaxEven(numbers1);
        cout << maxEven1 << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    try {
        cout << "Метод 2 (copy_if): ";
        int maxEven2 = MaxEvenFinder::FindMaxEvenAlternative(numbers1);
        cout << maxEven2 << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    try {
        cout << "Метод 3 (безопасный): ";
        int maxEven3 = MaxEvenFinder::FindMaxEvenSafe(numbers1);
        cout << maxEven3 << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    // 2. Тест с вектором без четных чисел
    cout << "\n2. Вектор без четных чисел:" << endl;
    cout << "=========================" << endl;

    vector<int> numbers2 = { 1, 3, 5, 7, 9, 11 };
    cout << "Вектор: ";
    for (int n : numbers2) cout << n << " ";
    cout << endl;

    vector<function<int(const vector<int>&)>> methods = {
        MaxEvenFinder::FindMaxEven,
        MaxEvenFinder::FindMaxEvenAlternative,
        MaxEvenFinder::FindMaxEvenSafe
    };

    vector<string> methodNames = { "Компаратор", "Copy_if", "Безопасный" };

    for (size_t i = 0; i < methods.size(); ++i) {
        try {
            cout << methodNames[i] << " метод: ";
            int result = methods[i](numbers2);
            cout << result << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }

    // 3. Тест с пустым вектором
    cout << "\n3. Пустой вектор:" << endl;
    cout << "================" << endl;

    vector<int> numbers3;
    cout << "Вектор: пустой" << endl;

    for (size_t i = 0; i < methods.size(); ++i) {
        try {
            cout << methodNames[i] << " метод: ";
            int result = methods[i](numbers3);
            cout << result << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

void demonstrateAdvancedUsage() {
    cout << "\n=== РАСШИРЕННОЕ ИСПОЛЬЗОВАНИЕ ===\n" << endl;

    // 1. Вектор с отрицательными числами
    cout << "1. Вектор с отрицательными числами:" << endl;
    cout << "=================================" << endl;

    vector<int> numbers = { -5, -2, -8, 3, 7, -4, 10, -6, 1 };
    cout << "Вектор: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    MaxEvenFinder::PrintVectorStats(numbers);

    // 2. Вектор с одним четным числом
    cout << "\n2. Вектор с одним четным числом:" << endl;
    cout << "==============================" << endl;

    vector<int> singleEven = { 42 };
    cout << "Вектор: ";
    for (int n : singleEven) cout << n << " ";
    cout << endl;

    try {
        int result = MaxEvenFinder::FindMaxEvenSafe(singleEven);
        cout << "Максимальное четное: " << result << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void demonstrateCorrectComparator() {
    cout << "\n=== ТЕСТИРОВАНИЕ КОРРЕКТНОГО КОМПАРАТОРА ===\n" << endl;

    // Тестовые векторы для проверки компаратора
    vector<vector<int>> testVectors = {
        {1, 2, 3, 4, 5},          
        {2, 4, 6, 8},              
        {1, 3, 5, 7},              
        {-4, -2, 0, 2, 4},         
        {10, 3, 8, 1, 6}          
    };

    for (size_t i = 0; i < testVectors.size(); ++i) {
        cout << "Тест " << i + 1 << ": ";
        for (int n : testVectors[i]) cout << n << " ";
        cout << endl;

        try {
            int result1 = MaxEvenFinder::FindMaxEven(testVectors[i]);
            int result2 = MaxEvenFinder::FindMaxEvenSafe(testVectors[i]);

            cout << "  Компаратор: " << result1 << ", Безопасный: " << result2;
            cout << " - " << (result1 == result2 ? "СОВПАДАЕТ" : "РАЗЛИЧАЕТСЯ") << endl;

        }
        catch (const exception& e) {
            cout << "  Ошибка: " << e.what() << endl;
        }
    }
}

void demonstrateSTLAlgorithmsSafe() {
    cout << "\n=== БЕЗОПАСНЫЕ АЛГОРИТМЫ STL ===\n" << endl;

    vector<int> numbers = { 15, 8, 23, 42, 17, 6, 31, 54, 9, 28 };

    cout << "Исходный вектор: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    // Безопасное использование алгоритмов STL

    // 1. count_if - подсчет четных чисел
    int evenCount = count_if(numbers.begin(), numbers.end(),
        [](int n) { return n % 2 == 0; });
    cout << "Количество четных чисел: " << evenCount << endl;

    // 2. Безопасный поиск с copy_if
    vector<int> evenNumbers;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evenNumbers),
        [](int n) { return n % 2 == 0; });

    if (!evenNumbers.empty()) {
        cout << "Четные числа: ";
        for (int n : evenNumbers) cout << n << " ";
        cout << endl;

        auto maxEven = max_element(evenNumbers.begin(), evenNumbers.end());
        auto minEven = min_element(evenNumbers.begin(), evenNumbers.end());

        cout << "Максимальное четное: " << *maxEven << endl;
        cout << "Минимальное четное: " << *minEven << endl;
    }
    else {
        cout << "Четных чисел нет" << endl;
    }

    // 3. Сортировка четных чисел
    if (!evenNumbers.empty()) {
        sort(evenNumbers.begin(), evenNumbers.end());
        cout << "Отсортированные четные числа: ";
        for (int n : evenNumbers) cout << n << " ";
        cout << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateMaxEvenFinding();
    demonstrateAdvancedUsage();
    demonstrateCorrectComparator();
    demonstrateSTLAlgorithmsSafe();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
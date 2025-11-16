#include <iostream>
#include <windows.h>
#include <vector>
#include "template_concepts.h"

using namespace std;

void demonstrateMaxOfTwo() {
    cout << "=== ШАБЛОННАЯ ФУНКЦИЯ maxOfTwo С ОГРАНИЧЕНИЯМИ ===\n" << endl;

    // 1. int
    cout << "1. Тип int:" << endl;
    int a = 10, b = 20;
    cout << "maxOfTwo(" << a << ", " << b << ") = " << maxOfTwo(a, b) << endl;

    // 2. double
    cout << "\n2. Тип double:" << endl;
    double x = 3.14, y = 2.71;
    cout << "maxOfTwo(" << x << ", " << y << ") = " << maxOfTwo(x, y) << endl;

    // 3. string
    cout << "\n3. Тип string:" << endl;
    string s1 = "apple", s2 = "banana";
    cout << "maxOfTwo(\"" << s1 << "\", \"" << s2 << "\") = \"" << maxOfTwo(s1, s2) << "\"" << endl;

    // 4. Пользовательский класс Product
    cout << "\n4. Пользовательский класс Product:" << endl;
    Product p1("Laptop", 999.99);
    Product p2("Smartphone", 699.99);
    cout << "maxOfTwo(" << p1 << ", " << p2 << ") = " << maxOfTwo(p1, p2) << endl;

    // 5. char
    cout << "\n5. Тип char:" << endl;
    char c1 = 'A', c2 = 'Z';
    cout << "maxOfTwo('" << c1 << "', '" << c2 << "') = '" << maxOfTwo(c1, c2) << "'" << endl;
}

void testWithContainers() {
    cout << "\n=== ИСПОЛЬЗОВАНИЕ С КОНТЕЙНЕРАМИ ===\n" << endl;

    vector<int> numbers = { 5, 2, 8, 1, 9, 3 };

    cout << "Поиск максимума в векторе:" << endl;
    cout << "Вектор: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        cout << numbers[i];
        if (i < numbers.size() - 1) cout << ", ";
    }
    cout << endl;

    if (!numbers.empty()) {
        int currentMax = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            currentMax = maxOfTwo(currentMax, numbers[i]);
        }
        cout << "Максимальный элемент: " << currentMax << endl;
    }
}

void demonstrateConceptEnforcement() {
    cout << "\n=== ПРОВЕРКА ОГРАНИЧЕНИЙ КОНЦЕПТОВ ===\n" << endl;

    // Этот код скомпилируется - int поддерживает <
    cout << "1. Корректное использование с int:" << endl;
    cout << "maxOfTwo(5, 10) = " << maxOfTwo(5, 10) << endl;

    // Этот код НЕ скомпилируется - раскомментируйте для проверки
    /*
    cout << "\n2. Попытка использования с NonComparable:" << endl;
    NonComparable nc1(1), nc2(2);
    // Ошибка компиляции: NonComparable не удовлетворяет концепту Comparable
    // auto result = maxOfTwo(nc1, nc2);
    cout << "Этот код не скомпилируется!" << endl;
    */

    cout << "\nКонцепт Comparable корректно ограничивает допустимые типы." << endl;
}

void benchmarkComparison() {
    cout << "\n=== СРАВНЕНИЕ РАЗЛИЧНЫХ ТИПОВ ===\n" << endl;

    // Сравнение разных пар значений
    vector<pair<string, string>> stringPairs = {
        {"apple", "zebra"},
        {"hello", "world"},
        {"cat", "dog"}
    };

    for (const auto& pair : stringPairs) {
        cout << "maxOfTwo(\"" << pair.first << "\", \"" << pair.second
            << "\") = \"" << maxOfTwo(pair.first, pair.second) << "\"" << endl;
    }

    cout << endl;

    // Сравнение продуктов
    vector<Product> products = {
        Product("Tablet", 299.99),
        Product("Monitor", 199.99),
        Product("Keyboard", 49.99),
        Product("Mouse", 25.99)
    };

    for (size_t i = 0; i < products.size() - 1; ++i) {
        cout << "Более дорогой продукт: " << maxOfTwo(products[i], products[i + 1]) << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateMaxOfTwo();
    testWithContainers();
    demonstrateConceptEnforcement();
    benchmarkComparison();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
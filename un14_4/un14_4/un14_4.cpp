#include <iostream>
#include <windows.h>
#include <vector>
#include <list>
#include <complex>
#include <algorithm>
#include <random>
#include "template_print.h"
#include "template_sorting.h"

using namespace std;

void demonstrateSortingCheck() {
    cout << "=== ПРОВЕРКА ОТСОРТИРОВАННОСТИ КОНТЕЙНЕРОВ ===\n" << endl;

    // 1. Отсортированный вектор int
    cout << "1. Вектор int:" << endl;
    vector<int> sortedInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int> unsortedInts = { 5, 2, 8, 1, 9, 3, 7, 4, 6, 10 };

    print_container_with_status(sortedInts, "Отсортированный вектор");
    print_container_with_status(unsortedInts, "Неотсортированный вектор");

    // 2. Вектор string
    cout << "\n2. Вектор string:" << endl;
    vector<string> sortedStrings = { "apple", "banana", "cherry", "date" };
    vector<string> unsortedStrings = { "zebra", "apple", "monkey", "banana" };

    print_container_with_status(sortedStrings, "Отсортированный вектор строк");
    print_container_with_status(unsortedStrings, "Неотсортированный вектор строк");

    // 3. List double
    cout << "\n3. List double:" << endl;
    list<double> sortedDoubles = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    list<double> unsortedDoubles = { 3.3, 1.1, 5.5, 2.2, 4.4 };

    print_container_with_status(sortedDoubles, "Отсортированный list");
    print_container_with_status(unsortedDoubles, "Неотсортированный list");

    // 4. Set (всегда отсортирован)
    cout << "\n4. Set (автоматически сортируется):" << endl;
    set<int> intSet = { 5, 2, 8, 1, 9, 3 };
    print_container_with_status(intSet, "Set");

    // 5. Проверка с итераторами
    cout << "\n5. Проверка с использованием итераторов:" << endl;
    vector<int> partialSorted = { 1, 2, 3, 5, 4, 6, 7 };

    cout << "Вектор: ";
    Print(partialSorted);

    // Проверка первой половины
    auto mid = partialSorted.begin() + 4;
    cout << "Первые 4 элемента: ";
    if (is_sorted(partialSorted.begin(), mid)) {
        cout << "ОТСОРТИРОВАНЫ";
    }
    else {
        cout << "НЕ ОТСОРТИРОВАНЫ";
    }
    cout << endl;

    // Проверка всей последовательности
    cout << "Вся последовательность: ";
    if (is_sorted(partialSorted.begin(), partialSorted.end())) {
        cout << "ОТСОРТИРОВАНА";
    }
    else {
        cout << "НЕ ОТСОРТИРОВАНА";
    }
    cout << endl;
}

void demonstrateConceptEnforcement() {
    cout << "\n=== ПРОВЕРКА ОГРАНИЧЕНИЙ КОНЦЕПТА Sortable ===\n" << endl;
        
    cout << "1. Корректное использование с vector<int>:" << endl;
    vector<int> numbers = { 1, 2, 3 };
    print_sorted_status(numbers, "vector<int>");
        
    cout << "\n2. Корректное использование с vector<string>:" << endl;
    vector<string> words = { "a", "b", "c" };
    print_sorted_status(words, "vector<string>");
        
    cout << "\n3. Попытка использования с vector<complex<double>>:" << endl;
    cout << "Закомментировано, т.к. complex<double> не поддерживает операции сравнения" << endl;
    /*
    vector<complex<double>> complexes = {{1, 2}, {3, 4}};
    // Ошибка компиляции: complex<double> не удовлетворяет концепту Sortable
    print_sorted_status(complexes, "vector<complex<double>>");
    */

    cout << "\nКонцепт Sortable корректно ограничивает допустимые типы." << endl;
}

void testEdgeCases() {
    cout << "\n=== ТЕСТИРОВАНИЕ ГРАНИЧНЫХ СЛУЧАЕВ ===\n" << endl;

    // 1. Пустой контейнер
    cout << "1. Пустой контейнер:" << endl;
    vector<int> empty;
    print_container_with_status(empty, "Пустой вектор");

    // 2. Контейнер из одного элемента
    cout << "\n2. Контейнер из одного элемента:" << endl;
    vector<int> single = { 42 };
    print_container_with_status(single, "Вектор из одного элемента");

    // 3. Контейнер с одинаковыми элементами
    cout << "\n3. Контейнер с одинаковыми элементами:" << endl;
    vector<int> sameElements = { 5, 5, 5, 5, 5 };
    print_container_with_status(sameElements, "Вектор с одинаковыми элементами");

    // 4. Почти отсортированный контейнер
    cout << "\n4. Почти отсортированный контейнер:" << endl;
    vector<int> almostSorted = { 1, 2, 3, 5, 4, 6, 7 };
    print_container_with_status(almostSorted, "Почти отсортированный вектор");

    // 5. Обратно отсортированный контейнер
    cout << "\n5. Обратно отсортированный контейнер:" << endl;
    vector<int> reverseSorted = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    print_container_with_status(reverseSorted, "Обратно отсортированный вектор");
}

void demonstrateWithSTLAlgorithms() {
    cout << "\n=== ИНТЕГРАЦИЯ С АЛГОРИТМАМИ STL ===\n" << endl;

    vector<int> data = { 9, 5, 2, 7, 1, 8, 3, 6, 4 };

    cout << "Исходный вектор: ";
    print_container_with_status(data, "До сортировки");

    // Сортировка по возрастанию
    sort(data.begin(), data.end());
    cout << "\nПосле std::sort (по возрастанию): ";
    print_container_with_status(data, "После сортировки");

    // Сортировка по убыванию
    sort(data.begin(), data.end(), greater<int>());
    cout << "\nПосле std::sort (по убыванию): ";
    print_container_with_status(data, "После сортировки по убыванию");

    // Перемешивание
    random_device rd;
    mt19937 g(rd());
    shuffle(data.begin(), data.end(), g);

    cout << "\nПосле shuffle: ";
    print_container_with_status(data, "После перемешивания");

    // Частичная сортировка
    vector<int> data2 = { 9, 5, 2, 7, 1, 8, 3, 6, 4 };
    partial_sort(data2.begin(), data2.begin() + 5, data2.end());

    cout << "\nПосле partial_sort (первые 5 элементов): ";
    print_container_with_status(data2, "После частичной сортировки");
}

void demonstrateCustomSorting() {
    cout << "\n=== ПОЛЬЗОВАТЕЛЬСКИЕ КРИТЕРИИ СОРТИРОВКИ ===\n" << endl;

    // Сортировка по абсолютному значению
    vector<int> numbers = { -5, 3, -2, 8, -1, 4, -7 };

    cout << "Исходный вектор: ";
    Print(numbers);

    // Создаем копию для сортировки по абсолютному значению
    vector<int> absSorted = numbers;
    sort(absSorted.begin(), absSorted.end(), [](int a, int b) {
        return abs(a) < abs(b);
        });

    cout << "После сортировки по абсолютному значению: ";
    Print(absSorted);
    print_sorted_status(absSorted, "По абсолютному значению");

    // Проверяем обычную сортировку
    vector<int> normalSorted = numbers;
    sort(normalSorted.begin(), normalSorted.end());

    cout << "После обычной сортировки: ";
    Print(normalSorted);
    print_sorted_status(normalSorted, "Обычная сортировка");
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateSortingCheck();
    demonstrateConceptEnforcement();
    testEdgeCases();
    demonstrateWithSTLAlgorithms();
    demonstrateCustomSorting();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
#include <iostream>
#include <windows.h>
#include <vector>
#include <list>
#include <set>
#include <array>
#include "template_print.h"

using namespace std;

// Пользовательский класс для демонстрации
class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    bool operator<(const Point& other) const {
        return (x * x + y * y) < (other.x * other.x + other.y * other.y);
    }
};

void demonstratePrintFunction() {
    cout << "=== ШАБЛОННАЯ ФУНКЦИЯ ВЫВОДА ДАННЫХ В ПОТОК ===\n" << endl;

    // 1. Вектор int
    cout << "1. Вектор int:" << endl;
    vector<int> intVector = { 1, 2, 3, 4, 5 };
    Print(intVector, ", ");
    Print(intVector, " -> ");

    // 2. Вектор string
    cout << "\n2. Вектор string:" << endl;
    vector<string> stringVector = { "apple", "banana", "cherry", "date" };
    Print(stringVector, " | ");

    // 3. List double
    cout << "\n3. List double:" << endl;
    list<double> doubleList = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    Print(doubleList, " ~ ");

    // 4. Set string
    cout << "\n4. Set string:" << endl;
    set<string> stringSet = { "zebra", "apple", "monkey", "banana" };
    Print(stringSet, " <-> ");

    // 5. C-массив
    cout << "\n5. C-массив:" << endl;
    int carr[] = { 10, 20, 30, 40, 50 };
    Print(carr, " :: ");

    // 6. Array
    cout << "\n6. Std::array:" << endl;
    array<float, 4> floatArray = { 1.5f, 2.5f, 3.5f, 4.5f };
    Print(floatArray, " +++ ");

    // 7. Пользовательский класс
    cout << "\n7. Вектор пользовательских объектов:" << endl;
    vector<Point> points = { Point(1, 2), Point(3, 4), Point(0, 0), Point(5, 1) };
    Print(points, " -> ");

    // 8. Set пользовательских объектов
    cout << "\n8. Set пользовательских объектов:" << endl;
    set<Point> pointSet = { Point(3, 4), Point(1, 1), Point(5, 5), Point(0, 2) };
    Print(pointSet, " | ");
}

void testDifferentDelimiters() {
    cout << "\n=== ТЕСТИРОВАНИЕ РАЗЛИЧНЫХ РАЗДЕЛИТЕЛЕЙ ===\n" << endl;

    vector<int> data = { 1, 2, 3, 4, 5 };

    cout << "Разделитель ', ': ";
    Print(data, ", ");

    cout << "Разделитель ' - ': ";
    Print(data, " - ");

    cout << "Разделитель ' -> ': ";
    Print(data, " -> ");

    cout << "Разделитель ' | ': ";
    Print(data, " | ");

    cout << "Разделитель пустой строки: ";
    Print(data, "");

    cout << "Разделитель с пробелами: ";
    Print(data, "   ");
}

void demonstrateEmptyContainers() {
    cout << "\n=== ТЕСТИРОВАНИЕ ПУСТЫХ КОНТЕЙНЕРОВ ===\n" << endl;

    cout << "Пустой вектор: ";
    vector<int> emptyVector;
    Print(emptyVector, ", ");

    cout << "Пустой список: ";
    list<string> emptyList;
    Print(emptyList, " | ");

    cout << "Пустой set: ";
    set<double> emptySet;
    Print(emptySet, " -> ");
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstratePrintFunction();
    testDifferentDelimiters();
    demonstrateEmptyContainers();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
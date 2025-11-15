#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "point_sorted.h"

using namespace std;

void demonstratePointSorting() {
    cout << "=== СОРТИРОВКА ТОЧЕК В ВЕКТОРЕ ПО РАССТОЯНИЮ ДО ЦЕНТРА ===\n" << endl;

    // 1. Создание вектора точек
    vector<Point> points;

    // Добавление точек в вектор
    points.push_back(Point(1, 2));
    points.push_back(Point(10, 12));
    points.push_back(Point(21, 7));
    points.push_back(Point(4, 8));
    points.push_back(Point(15, 3));
    points.push_back(Point(7, 9));
    points.push_back(Point(0, 5));
    points.push_back(Point(12, 0));

    // 2. Вывод исходного вектора
    cout << "Исходный вектор точек:" << endl;
    for (const auto& point : points) {
        cout << point << endl;
    }

    // 3. Сортировка точек по расстоянию до центра
    cout << "\nСортировка точек по расстоянию до центра координат..." << endl;
    sort(points.begin(), points.end());

    // 4. Вывод отсортированного вектора
    cout << "\nОтсортированный вектор точек:" << endl;
    for (const auto& point : points) {
        cout << point << endl;
    }

    // 5. Дополнительные операции с отсортированным вектором
    cout << "\nДополнительная информация:" << endl;
    if (!points.empty()) {
        cout << "Ближайшая точка к центру: " << points.front() << endl;
        cout << "Самая удаленная точка от центра: " << points.back() << endl;
    }
}

void demonstrateAdvancedPointOperations() {
    cout << "\n=== РАСШИРЕННЫЕ ОПЕРАЦИИ С ТОЧКАМИ ===\n" << endl;

    // 1. Создание случайных точек
    vector<Point> randomPoints;
    mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> distribution(-10.0, 10.0);

    for (int i = 0; i < 8; ++i) {
        double x = distribution(generator);
        double y = distribution(generator);
        randomPoints.push_back(Point(x, y));
    }

    cout << "Случайные точки:" << endl;
    for (const auto& point : randomPoints) {
        cout << point << endl;
    }

    // 2. Сортировка
    sort(randomPoints.begin(), randomPoints.end());

    cout << "\nОтсортированные случайные точки:" << endl;
    for (const auto& point : randomPoints) {
        cout << point << endl;
    }

    // 3. Поиск точек в определенном диапазоне расстояний
    cout << "\nТочки на расстоянии от 5 до 10 от центра:" << endl;
    for (const auto& point : randomPoints) {
        double dist = point.distanceToOrigin();
        if (dist >= 5.0 && dist <= 10.0) {
            cout << point << endl;
        }
    }

    // 4. Использование алгоритмов STL
    cout << "\nИспользование алгоритмов STL:" << endl;

    // Поиск точки с минимальным расстоянием
    auto minIt = min_element(randomPoints.begin(), randomPoints.end());
    if (minIt != randomPoints.end()) {
        cout << "Минимальное расстояние: " << *minIt << endl;
    }

    // Поиск точки с максимальным расстоянием
    auto maxIt = max_element(randomPoints.begin(), randomPoints.end());
    if (maxIt != randomPoints.end()) {
        cout << "Максимальное расстояние: " << *maxIt << endl;
    }

    // Подсчет точек в первой четверти
    int firstQuadrantCount = count_if(randomPoints.begin(), randomPoints.end(),
        [](const Point& p) { return p.getX() > 0 && p.getY() > 0; });
    cout << "Точек в первой четверти: " << firstQuadrantCount << endl;
}

void testPointComparisons() {
    cout << "\n=== ТЕСТИРОВАНИЕ ОПЕРАТОРОВ СРАВНЕНИЯ ===\n" << endl;

    Point p1(3, 4);  // расстояние = 5
    Point p2(6, 8);  // расстояние = 10
    Point p3(3, 4);  // расстояние = 5 (равна p1)
    Point p4(1, 1);  // расстояние ≈ 1.41

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;

    cout << "\nРезультаты сравнения:" << endl;
    cout << "p1 < p2: " << (p1 < p2) << " (ожидается: 1)" << endl;
    cout << "p1 > p2: " << (p1 > p2) << " (ожидается: 0)" << endl;
    cout << "p1 <= p3: " << (p1 <= p3) << " (ожидается: 1)" << endl;
    cout << "p1 >= p3: " << (p1 >= p3) << " (ожидается: 1)" << endl;
    cout << "p1 == p3: " << (p1 == p3) << " (ожидается: 1)" << endl;
    cout << "p1 == p2: " << (p1 == p2) << " (ожидается: 0)" << endl;
    cout << "p1 != p2: " << (p1 != p2) << " (ожидается: 1)" << endl;
    cout << "p4 < p1: " << (p4 < p1) << " (ожидается: 1)" << endl;
    cout << "p4 > p1: " << (p4 > p1) << " (ожидается: 0)" << endl;
}

void demonstrateCustomSorting() {
    cout << "\n=== ПОЛЬЗОВАТЕЛЬСКИЕ ВАРИАНТЫ СОРТИРОВКИ ===\n" << endl;

    vector<Point> points = {
        Point(3, 4),
        Point(1, 1),
        Point(6, 8),
        Point(0, 5),
        Point(2, 2)
    };

    // 1. Сортировка по расстоянию до центра (по умолчанию)
    cout << "Сортировка по расстоянию до центра:" << endl;
    sort(points.begin(), points.end());
    for (const auto& p : points) {
        cout << p << endl;
    }

    // 2. Сортировка по координате X
    cout << "\nСортировка по координате X:" << endl;
    sort(points.begin(), points.end(),
        [](const Point& a, const Point& b) { return a.getX() < b.getX(); });
    for (const auto& p : points) {
        cout << p << endl;
    }

    // 3. Сортировка по координате Y
    cout << "\nСортировка по координате Y:" << endl;
    sort(points.begin(), points.end(),
        [](const Point& a, const Point& b) { return a.getY() < b.getY(); });
    for (const auto& p : points) {
        cout << p << endl;
    }

    // 4. Сортировка по сумме координат
    cout << "\nСортировка по сумме координат (x + y):" << endl;
    sort(points.begin(), points.end(),
        [](const Point& a, const Point& b) {
            return (a.getX() + a.getY()) < (b.getX() + b.getY());
        });
    for (const auto& p : points) {
        cout << p << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstratePointSorting();
    demonstrateAdvancedPointOperations();
    testPointComparisons();
    demonstrateCustomSorting();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
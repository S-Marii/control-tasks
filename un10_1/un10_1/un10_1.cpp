#include <iostream>
#include <windows.h>
#include "dot.h"
#include "triangle_composition.h"
#include "triangle_aggregation.h"

using namespace std;

// Демонстрация композиции
void demonstrateComposition() {
    cout << "\n=== ДЕМОНСТРАЦИЯ КОМПОЗИЦИИ ===" << endl;
    cout << "Точки создаются и уничтожаются вместе с треугольником\n" << endl;

    try {
        // 1. Треугольник по умолчанию
        cout << "1. Треугольник по умолчанию:" << endl;
        TriangleComposition t1;

        // 2. Треугольник по координатам
        cout << "\n2. Треугольник по координатам:" << endl;
        TriangleComposition t2(0, 0, 3, 0, 0, 4);

        // 3. Треугольник из временных объектов точек
        cout << "\n3. Треугольник из временных объектов:" << endl;
        TriangleComposition t3(Dot(1, 1), Dot(4, 1), Dot(1, 5));

        // 4. Попытка создания недопустимого треугольника
        cout << "\n4. Попытка создания недопустимого треугольника:" << endl;
        try {
            TriangleComposition t4(0, 0, 1, 1, 2, 2); // Точки на одной прямой
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

    }
    catch (const exception& e) {
        cout << "Неожиданная ошибка: " << e.what() << endl;
    }

    cout << "\n--- Завершение блока композиции ---" << endl;
}

// Демонстрация агрегации
void demonstrateAggregation() {
    cout << "\n=== ДЕМОНСТРАЦИЯ АГРЕГАЦИИ ===" << endl;
    cout << "Точки существуют независимо от треугольника\n" << endl;

    try {
        // 1. Создаем точки отдельно
        cout << "1. Создание точек:" << endl;
        Dot pointA(0, 0);
        Dot pointB(3, 0);
        Dot pointC(0, 4);

        // 2. Создаем треугольник из существующих точек
        cout << "\n2. Создание треугольника из существующих точек:" << endl;
        TriangleAggregation t1(&pointA, &pointB, &pointC);

        // 3. Изменяем вершины треугольника
        cout << "\n3. Изменение вершин треугольника:" << endl;
        Dot pointD(2, 0);
        Dot pointE(5, 0);
        Dot pointF(2, 3);

        TriangleAggregation t2;
        t2.setVertexA(&pointD);
        t2.setVertexB(&pointE);
        t2.setVertexC(&pointF);
        t2.displayInfo();

        // 4. Один треугольник с разными наборами точек
        cout << "\n4. Один треугольник с разными наборами точек:" << endl;
        TriangleAggregation dynamicTriangle;

        // Первый набор точек
        Dot* dynPoint1 = new Dot(1, 1);
        Dot* dynPoint2 = new Dot(4, 1);
        Dot* dynPoint3 = new Dot(1, 4);

        dynamicTriangle.setVertexA(dynPoint1);
        dynamicTriangle.setVertexB(dynPoint2);
        dynamicTriangle.setVertexC(dynPoint3);
        dynamicTriangle.displayInfo();

        // Второй набор точек (те же указатели можно переиспользовать)
        cout << "\nИзменяем вершины треугольника:" << endl;
        Dot* dynPoint4 = new Dot(0, 0);
        Dot* dynPoint5 = new Dot(6, 0);
        Dot* dynPoint6 = new Dot(0, 8);

        dynamicTriangle.setVertexA(dynPoint4);
        dynamicTriangle.setVertexB(dynPoint5);
        dynamicTriangle.setVertexC(dynPoint6);
        dynamicTriangle.displayInfo();

        // Очистка динамической памяти
        delete dynPoint1;
        delete dynPoint2;
        delete dynPoint3;
        delete dynPoint4;
        delete dynPoint5;
        delete dynPoint6;

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    cout << "\n--- Завершение блока агрегации ---" << endl;
}

// Сравнение двух подходов
void compareApproaches() {
    cout << "\n=== СРАВНЕНИЕ КОМПОЗИЦИИ И АГРЕГАЦИИ ===" << endl;

    cout << "\nКОМПОЗИЦИЯ:" << endl;
    cout << "- Точки создаются внутри треугольника" << endl;
    cout << "- Точки уничтожаются вместе с треугольником" << endl;
    cout << "- Более простая управление памятью" << endl;
    cout << "- Меньшая гибкость" << endl;

    cout << "\nАГРЕГАЦИЯ:" << endl;
    cout << "- Точки создаются отдельно от треугольника" << endl;
    cout << "- Точки могут переиспользоваться" << endl;
    cout << "- Более сложное управление памятью" << endl;
    cout << "- Большая гибкость" << endl;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "=== РЕАЛИЗАЦИЯ ОТНОШЕНИЙ МЕЖДУ КЛАССАМИ ===" << endl;
    cout << "Класс Triangle и класс Dot\n" << endl;

    demonstrateComposition();
    demonstrateAggregation();
    compareApproaches();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
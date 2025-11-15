#include <iostream>
#include <windows.h>
#include "triangle.h"

using namespace std;

// Функция для демонстрации работы с треугольником
void demonstrateTriangle() {
    cout << "\n=== Демонстрация работы класса Triangle ===\n" << endl;

    try {
        // 1. Создание корректных треугольников
        cout << "1. Корректные треугольники:" << endl;
        Triangle t1(3, 4, 5);
        Triangle t2(5, 5, 5);
        Triangle t3(6, 8, 10);

        // 2. Попытка создания недопустимых треугольников
        cout << "\n2. Попытка создания недопустимых треугольников:" << endl;

        try {
            Triangle t4(1, 2, 10); // Нарушение неравенства треугольника
        }
        catch (const Triangle::InvalidTriangleError& e) {
            cout << "Перехвачено исключение: ";
            e.printDetails();
        }

        try {
            Triangle t5(-1, 2, 3); // Отрицательная сторона
        }
        catch (const Triangle::InvalidTriangleError& e) {
            cout << "Перехвачено исключение: ";
            e.printDetails();
        }

        try {
            Triangle t6(0, 4, 5); // Нулевая сторона
        }
        catch (const Triangle::InvalidTriangleError& e) {
            cout << "Перехвачено исключение: ";
            e.printDetails();
        }

        // 3. Изменение сторон с проверкой
        cout << "\n3. Изменение сторон треугольника:" << endl;
        Triangle t7(2, 3, 4);

        try {
            t7.setSideA(10); // Попытка установить недопустимую сторону
        }
        catch (const Triangle::InvalidTriangleError& e) {
            cout << "Ошибка при изменении стороны: ";
            e.printDetails();
        }

        // Корректное изменение
        t7.setSideA(3);
        t7.display();

        // 4. Массив треугольников с обработкой исключений
        cout << "\n4. Работа с массивом треугольников:" << endl;
        Triangle triangles[] = {
            Triangle(3, 4, 5),
            Triangle(5, 12, 13),
            Triangle(8, 15, 17)
        };

        // Попытка добавить недопустимый треугольник в динамический массив
        cout << "\n5. Динамическое создание треугольников:" << endl;
        Triangle* dynamicTriangles[5];
        int count = 0;

        double sides[][3] = {
            {2, 3, 4},
            {1, 1, 1},
            {10, 1, 1}, // Неправильный
            {7, 8, 9},
            {0, 4, 5}   // Неправильный
        };

        for (int i = 0; i < 5; ++i) {
            try {
                dynamicTriangles[count] = new Triangle(sides[i][0], sides[i][1], sides[i][2]);
                count++;
            }
            catch (const Triangle::InvalidTriangleError& e) {
                cout << "Не удалось создать треугольник " << (i + 1) << ": ";
                e.printDetails();
            }
        }

        cout << "\nУспешно создано " << count << " треугольников:" << endl;
        for (int i = 0; i < count; ++i) {
            dynamicTriangles[i]->display();
            delete dynamicTriangles[i];
        }

    }
    catch (const exception& e) {
        cout << "Неожиданная ошибка: " << e.what() << endl;
    }
}

// Функция для интерактивного создания треугольника
void interactiveTriangleCreation() {
    cout << "\n=== Интерактивное создание треугольника ===" << endl;

    double a, b, c;

    while (true) {
        cout << "\nВведите три стороны треугольника (0 0 0 для выхода): ";
        cin >> a >> b >> c;

        if (a == 0 && b == 0 && c == 0) {
            break;
        }

        try {
            Triangle t(a, b, c);
            cout << "Треугольник успешно создан!" << endl;
            t.display();
        }
        catch (const Triangle::InvalidTriangleError& e) {
            cout << "Ошибка создания треугольника: ";
            e.printDetails();
            cout << "Попробуйте снова." << endl;
        }
        catch (const exception& e) {
            cout << "Общая ошибка: " << e.what() << endl;
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateTriangle();
    interactiveTriangleCreation();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
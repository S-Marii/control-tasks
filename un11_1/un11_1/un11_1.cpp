#include <iostream>
#include <windows.h>
#include "time_operators.h"

using namespace std;

void demonstrateTimeOperators() {
    cout << "=== ДЕМОНСТРАЦИЯ ПЕРЕГРУЗКИ ОПЕРАТОРОВ В КЛАССЕ TIME ===\n" << endl;

    try {
        // 1. Создание объектов Time
        cout << "1. Создание объектов Time:" << endl;
        Time t1(10, 30, 45);
        Time t2(2, 45, 15);
        Time t3(1, 15, 30);

        cout << "t1 = " << t1 << endl;
        cout << "t2 = " << t2 << endl;
        cout << "t3 = " << t3 << endl;

        // 2. Сложение и вычитание объектов Time
        cout << "\n2. Арифметические операции с объектами Time:" << endl;
        Time sum = t1 + t2;
        Time diff = t1 - t2;

        cout << "t1 + t2 = " << sum << endl;
        cout << "t1 - t2 = " << diff << endl;

        // 3. Цепочка операций
        cout << "\n3. Цепочка операций:" << endl;
        Time chain = t1 + t2 + t3;
        cout << "t1 + t2 + t3 = " << chain << endl;

        // 4. Операции с double
        cout << "\n4. Операции с double:" << endl;
        Time t4 = t1 + 1.5;  // Time + double
        Time t5 = 2.25 + t1; // double + Time
        Time t6 = t1 - 0.75; // Time - double

        cout << "t1 + 1.5 часа = " << t4 << endl;
        cout << "2.25 часа + t1 = " << t5 << endl;
        cout << "t1 - 0.75 часа = " << t6 << endl;

        // 5. Операторы сравнения
        cout << "\n5. Операторы сравнения:" << endl;
        cout << "t1 == t2: " << (t1 == t2) << endl;
        cout << "t1 != t2: " << (t1 != t2) << endl;
        cout << "t1 < t2: " << (t1 < t2) << endl;
        cout << "t1 > t2: " << (t1 > t2) << endl;
        cout << "t1 <= t2: " << (t1 <= t2) << endl;
        cout << "t1 >= t2: " << (t1 >= t2) << endl;

        // 6. Операторы присваивания
        cout << "\n6. Операторы присваивания:" << endl;
        Time t7 = t1;
        t7 += t2;
        cout << "t1 += t2: " << t7 << endl;

        Time t8 = t1;
        t8 -= t3;
        cout << "t1 -= t3: " << t8 << endl;

        // 7. Преобразование типов
        cout << "\n7. Преобразование типов:" << endl;
        double hours = static_cast<double>(t1);
        int seconds = static_cast<int>(t1);

        cout << "t1 в часах (double): " << hours << endl;
        cout << "t1 в секундах (int): " << seconds << endl;

        // 8. Ввод времени с клавиатуры
        cout << "\n8. Ввод времени с клавиатуры:" << endl;
        Time inputTime;
        cout << "Введите время в формате HH:MM:SS: ";
        cin >> inputTime;
        cout << "Вы ввели: " << inputTime << endl;

        // 9. Граничные случаи
        cout << "\n9. Граничные случаи:" << endl;
        Time midnight(23, 59, 59);
        Time oneSecond(0, 0, 1);
        Time afterMidnight = midnight + oneSecond;
        cout << "23:59:59 + 00:00:01 = " << afterMidnight << endl;

        Time large(0, 120, 120); // 2 часа 2 минуты
        cout << "00:120:120 после нормализации = " << large << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void testErrorCases() {
    cout << "\n=== ТЕСТИРОВАНИЕ ОШИБОЧНЫХ СЛУЧАЕВ ===" << endl;

    try {
        Time t1(1, 0, 0);
        Time t2(2, 0, 0);

        // Попытка вычесть большее время из меньшего
        cout << "\nПопытка вычесть большее время из меньшего:" << endl;
        Time error = t1 - t2; // Должно вызвать исключение

    }
    catch (const exception& e) {
        cout << "Перехвачено исключение: " << e.what() << endl;
    }

    try {
        Time t3(1, 0, 0);

        // Попытка вычесть слишком много часов
        cout << "\nПопытка вычесть слишком много часов:" << endl;
        Time error = t3 - 2.0; // Должно вызвать исключение

    }
    catch (const exception& e) {
        cout << "Перехвачено исключение: " << e.what() << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateTimeOperators();
    testErrorCases();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
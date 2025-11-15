#include <iostream>
#include <windows.h>
#include "safe_time.h"

using namespace std;

// Функция для демонстрации работы с безопасным временем
void demonstrateSafeTime() {
    cout << "\n=== Демонстрация работы класса SafeTime ===\n" << endl;

    try {
        // 1. Создание корректных объектов времени
        cout << "1. Корректное создание времени:" << endl;
        SafeTime t1;
        t1.display("Время по умолчанию");

        SafeTime t2(10, 30, 45);
        t2.display("Время 1");

        SafeTime t3(23, 59, 59);
        t3.display("Время 2");

        // 2. Попытка создания недопустимого времени
        cout << "\n2. Попытка создания недопустимого времени:" << endl;

        try {
            SafeTime t4(-1, 30, 45); // Отрицательные часы
        }
        catch (const SafeTime::InvalidTimeError& e) {
            cout << "Перехвачено исключение: ";
            e.printDetails();
        }

        try {
            SafeTime t5(10, 70, 45); // Неправильные минуты
        }
        catch (const SafeTime::InvalidTimeError& e) {
            cout << "Перехвачено исключение: ";
            e.printDetails();
        }

        try {
            SafeTime t6(25, 30, 45); // Часы >= 24
        }
        catch (const SafeTime::InvalidTimeError& e) {
            cout << "Перехвачено исключение: ";
            e.printDetails();
        }

        // 3. Операции с временем
        cout << "\n3. Арифметические операции:" << endl;
        SafeTime start(10, 30, 0);
        SafeTime duration(1, 45, 30);

        SafeTime end = start + duration;
        start.display("Начальное время");
        duration.display("Длительность");
        end.display("Конечное время");

        // 4. Опасные операции
        cout << "\n4. Опасные операции:" << endl;
        SafeTime smallTime(1, 0, 0);
        SafeTime largeTime(2, 30, 0);

        try {
            SafeTime diff = smallTime - largeTime; // Попытка вычесть большее из меньшего
        }
        catch (const SafeTime::TimeOperationError& e) {
            cout << "Ошибка операции: ";
            e.printDetails();
        }

        // Корректное вычитание
        SafeTime diff = largeTime - smallTime;
        diff.display("Разность (большее - меньшее)");

        // 5. Работа с операторами
        cout << "\n5. Работа с операторами:" << endl;
        SafeTime timeA(5, 0, 0);
        SafeTime timeB(5, 0, 0);
        SafeTime timeC(6, 0, 0);

        cout << "timeA == timeB: " << (timeA == timeB) << endl;
        cout << "timeA != timeC: " << (timeA != timeC) << endl;
        cout << "timeA < timeC: " << (timeA < timeC) << endl;
        cout << "timeC > timeA: " << (timeC > timeA) << endl;

        // 6. Преобразование из секунд
        cout << "\n6. Преобразование из секунд:" << endl;
        SafeTime fromSec;
        fromSec.fromSeconds(3661); // 1 час 1 минута 1 секунда
        fromSec.display("3661 секунд");

        try {
            fromSec.fromSeconds(-100); // Отрицательные секунды
        }
        catch (const SafeTime::TimeOperationError& e) {
            cout << "Ошибка преобразования: ";
            e.printDetails();
        }

    }
    catch (const exception& e) {
        cout << "Неожиданная ошибка: " << e.what() << endl;
    }
}

// Функция для тестирования граничных случаев
void testBoundaryCases() {
    cout << "\n=== Тестирование граничных случаев ===\n" << endl;

    try {
        // Граничные значения
        SafeTime t1(0, 0, 0);    // Минимальное время
        SafeTime t2(23, 59, 59); // Максимальное время
        t1.display("Минимальное время");
        t2.display("Максимальное время");

        // Переполнение
        cout << "\nПереполнение времени:" << endl;
        SafeTime t3(22, 30, 0);
        SafeTime t4(2, 45, 0);
        SafeTime sum = t3 + t4; // 25:15:00 -> 01:15:00 после нормализации
        t3.display("Время 1");
        t4.display("Время 2");
        sum.display("Сумма с переполнением");

        // Нормализация больших значений
        cout << "\nНормализация больших значений:" << endl;
        SafeTime t5(0, 120, 120); // 2 часа 2 минуты
        t5.display("После нормализации");

        // Сложение с большими значениями
        cout << "\nСложение с большими значениями:" << endl;
        SafeTime t6(0, 50, 50);
        SafeTime t7(0, 50, 50);
        SafeTime sum2 = t6 + t7; // 1 час 41 минута 40 секунд
        t6.display("Время A");
        t7.display("Время B");
        sum2.display("Сумма A + B");

    }
    catch (const exception& e) {
        cout << "Ошибка в граничных случаях: " << e.what() << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateSafeTime();
    testBoundaryCases();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
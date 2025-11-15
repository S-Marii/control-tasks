#include <iostream>
#include <windows.h>
#include "time.h"

using namespace std;

// Функция для ввода времени с клавиатуры
Time inputTime(const string& prompt) {
    cout << prompt << endl;
    int h, m, s;

    cout << "Часы: ";
    cin >> h;
    cout << "Минуты: ";
    cin >> m;
    cout << "Секунды: ";
    cin >> s;

    return Time(h, m, s);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "=== Демонстрация работы класса Time ===\n" << endl;

    try {
        // Создание объектов разными способами
        cout << "1. Создание объектов:" << endl;

        // Константный объект с конструктором по умолчанию
        const Time zeroTime;
        zeroTime.display("Время по умолчанию");

        // Объект с конструктором с параметрами
        Time time1(10, 30, 45);
        time1.display("Время 1 (10:30:45)");

        // Объект с "неправильными" значениями
        Time time2(1, 70, 125);
        time2.display("Время 2 (1:70:125) после нормализации");

        // Ввод времени с клавиатуры
        cout << "\n2. Ввод времени с клавиатуры:" << endl;
        Time time3 = inputTime("Введите первое время:");
        time3.display("Вы ввели");

        Time time4 = inputTime("Введите второе время:");
        time4.display("Вы ввели");

        // Демонстрация сложения времени
        cout << "\n3. Сложение интервалов времени:" << endl;
        time3.display("Время 1");
        time4.display("Время 2");
        Time sum = time3.add(time4);
        sum.display("Результат сложения");

        // Демонстрация вычитания времени
        cout << "\n4. Вычитание интервалов времени:" << endl;
        time3.display("Время 1");
        time4.display("Время 2");

        if (time3.toSeconds() >= time4.toSeconds()) {
            Time diff = time3.subtract(time4);
            diff.display("Результат вычитания (time1 - time2)");
        }
        else {
            Time diff = time4.subtract(time3);
            diff.display("Результат вычитания (time2 - time1)");
            cout << "Примечание: вычиталось из большего времени" << endl;
        }

        // Демонстрация преобразования в секунды
        cout << "\n5. Преобразование в секунды:" << endl;
        cout << "Время 1 в секундах: " << time1.toSeconds() << " сек" << endl;
        cout << "Время 2 в секундах: " << time2.toSeconds() << " сек" << endl;
        cout << "Время 3 в секундах: " << time3.toSeconds() << " сек" << endl;
        cout << "Время 4 в секундах: " << time4.toSeconds() << " сек" << endl;

        // Демонстрация работы с динамическими объектами
        cout << "\n6. Работа с динамическими объектами:" << endl;
        Time* dynamicTime = new Time(23, 59, 59);
        dynamicTime->display("Динамический объект");

        // Сложение с динамическим объектом
        Time result = time1.add(*dynamicTime);
        result.display("Сумма с динамическим объектом");

        // Явное удаление динамического объекта
        cout << "Удаляем динамический объект..." << endl;
        delete dynamicTime;

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    cout << "\nПрограмма завершена. Автоматическое уничтожение объектов..." << endl;
    return 0;
}
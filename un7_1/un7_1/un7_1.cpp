#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

struct Time {
    int hours;
    int minutes;
    int seconds;

    // Конструктор для инициализации
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    // Функция для нормализации времени
    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24;
        }

        // Обработка отрицательных значений
        if (seconds < 0) {
            minutes -= 1 + abs(seconds) / 60;
            seconds = 60 - (abs(seconds) % 60);
        }
        if (minutes < 0) {
            hours -= 1 + abs(minutes) / 60;
            minutes = 60 - (abs(minutes) % 60);
        }
        if (hours < 0) {
            hours = 24 - (abs(hours) % 24);
        }
    }

    // Функция для получения общего количества секунд
    int toSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    // Функция сложения интервалов времени
    Time add(const Time& other) const {
        Time result(hours + other.hours, minutes + other.minutes, seconds + other.seconds);
        result.normalize();
        return result;
    }

    // Функция вычитания интервалов времени
    Time subtract(const Time& other) const {
        Time result(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
        result.normalize();
        return result;
    }

    // Функция для вывода времени
    void show() const {
        cout << hours << "ч " << minutes << "м " << seconds << "с";
    }

    // Функция для вывода времени в формате HH:MM:SS
    void showFormatted() const {
        cout << (hours < 10 ? "0" : "") << hours << ":"
            << (minutes < 10 ? "0" : "") << minutes << ":"
            << (seconds < 10 ? "0" : "") << seconds;
    }
};

// Функция для ввода времени
Time inputTime() {
    int h, m, s;

    cout << "Введите время:\n";
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

    cout << "=== Работа со структурой Time ===\n";

    // Ввод первого времени
    cout << "Первое время:\n";
    Time t1 = inputTime();

    // Ввод второго времени
    cout << "\nВторое время:\n";
    Time t2 = inputTime();

    // Вывод введенных времен
    cout << "\nВведенные времена:\n";
    cout << "Время 1: "; t1.showFormatted(); cout << endl;
    cout << "Время 2: "; t2.showFormatted(); cout << endl;

    // Вывод количества секунд
    cout << "\nКоличество секунд:\n";
    cout << "Время 1: " << t1.toSeconds() << " секунд\n";
    cout << "Время 2: " << t2.toSeconds() << " секунд\n";

    // Сложение времен
    Time sum = t1.add(t2);
    cout << "\nСумма времен: ";
    sum.showFormatted();
    cout << " ("; sum.show(); cout << ")\n";

    // Вычитание времен
    Time diff = t1.subtract(t2);
    cout << "Разность времен: ";
    diff.showFormatted();
    cout << " ("; diff.show(); cout << ")\n";

    return 0;
}
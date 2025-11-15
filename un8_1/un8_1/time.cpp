#include "time.h"
#include <stdexcept>
#include <iomanip>

using namespace std;

// Конструктор по умолчанию
Time::Time() : hours(0), minutes(0), seconds(0) {
    cout << "Создан объект Time (по умолчанию): ";
    display();
}

// Конструктор с параметрами
Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    normalize();
    cout << "Создан объект Time (с параметрами): ";
    display();
}

// Деструктор
Time::~Time() {
    cout << "Уничтожен объект Time: ";
    display();
}

// Установка часов с проверкой
void Time::setHours(int h) {
    if (h < 0) {
        throw invalid_argument("Часы не могут быть отрицательными");
    }
    hours = h;
}

// Установка минут с проверкой
void Time::setMinutes(int m) {
    if (m < 0) {
        throw invalid_argument("Минуты не могут быть отрицательными");
    }
    minutes = m;
}

// Установка секунд с проверкой
void Time::setSeconds(int s) {
    if (s < 0) {
        throw invalid_argument("Секунды не могут быть отрицательными");
    }
    seconds = s;
}

// Нормализация времени
void Time::normalize() {
    // Обработка секунд
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }

    // Обработка минут
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }

    // Обработка часов
    if (hours >= 24) {
        hours %= 24;
    }
}

// Вывод времени в формате HH:MM:SS
void Time::display() const {
    cout << setfill('0') << setw(2) << hours << ":"
        << setfill('0') << setw(2) << minutes << ":"
        << setfill('0') << setw(2) << seconds << endl;
}

// Вывод времени с меткой
void Time::display(const string& label) const {
    cout << label << ": "
        << setfill('0') << setw(2) << hours << ":"
        << setfill('0') << setw(2) << minutes << ":"
        << setfill('0') << setw(2) << seconds << endl;
}

// Преобразование времени в секунды
int Time::toSeconds() const {
    return hours * 3600 + minutes * 60 + seconds;
}

// Сложение двух интервалов времени
Time Time::add(const Time& other) const {
    Time result;
    result.hours = hours + other.hours;
    result.minutes = minutes + other.minutes;
    result.seconds = seconds + other.seconds;
    result.normalize();
    return result;
}

// Вычитание интервалов времени
Time Time::subtract(const Time& other) const {
    int totalSeconds1 = toSeconds();
    int totalSeconds2 = other.toSeconds();

    if (totalSeconds1 < totalSeconds2) {
        // Если первое время меньше второго, возвращаем нулевое время
        return Time();
    }

    int diffSeconds = totalSeconds1 - totalSeconds2;
    Time result;
    result.hours = diffSeconds / 3600;
    result.minutes = (diffSeconds % 3600) / 60;
    result.seconds = diffSeconds % 60;
    result.normalize();

    return result;
}
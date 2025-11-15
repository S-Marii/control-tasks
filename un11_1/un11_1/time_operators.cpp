#include "time_operators.h"
#include <stdexcept>

using namespace std;

// Конструктор по умолчанию
Time::Time() : hours(0), minutes(0), seconds(0) {}

// Конструктор с параметрами
Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    normalize();
}

// Деструктор
Time::~Time() {
    // Деструктор пустой, так как нет динамической памяти
}

// Нормализация времени
void Time::normalize() {
    // Обработка секунд
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    else if (seconds < 0) {
        int borrow = (-seconds + 59) / 60;
        minutes -= borrow;
        seconds += borrow * 60;
    }

    // Обработка минут
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    else if (minutes < 0) {
        int borrow = (-minutes + 59) / 60;
        hours -= borrow;
        minutes += borrow * 60;
    }

    // Обработка часов
    if (hours < 0) {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
}

// Преобразование времени в секунды
int Time::toSeconds() const {
    return hours * 3600 + minutes * 60 + seconds;
}

// Преобразование из секунд
void Time::fromSeconds(int totalSeconds) {
    if (totalSeconds < 0) {
        throw invalid_argument("Нельзя преобразовать отрицательное количество секунд");
    }

    hours = totalSeconds / 3600;
    minutes = (totalSeconds % 3600) / 60;
    seconds = totalSeconds % 60;
    normalize();
}

// Вывод времени
void Time::display() const {
    cout << *this;
}

// Перегрузка оператора сложения Time + Time
Time Time::operator+(const Time& other) const {
    Time result(hours + other.hours,
        minutes + other.minutes,
        seconds + other.seconds);
    return result;
}

// Перегрузка оператора вычитания Time - Time
Time Time::operator-(const Time& other) const {
    int totalSeconds1 = toSeconds();
    int totalSeconds2 = other.toSeconds();

    if (totalSeconds1 < totalSeconds2) {
        throw invalid_argument("Нельзя вычесть большее время из меньшего");
    }

    Time result;
    result.fromSeconds(totalSeconds1 - totalSeconds2);
    return result;
}

// Перегрузка оператора сложения Time + double
Time Time::operator+(double hoursToAdd) const {
    int additionalSeconds = static_cast<int>(hoursToAdd * 3600);
    Time result;
    result.fromSeconds(toSeconds() + additionalSeconds);
    return result;
}

// Перегрузка оператора вычитания Time - double
Time Time::operator-(double hoursToSubtract) const {
    int subtractSeconds = static_cast<int>(hoursToSubtract * 3600);
    int currentSeconds = toSeconds();

    if (currentSeconds < subtractSeconds) {
        throw invalid_argument("Нельзя вычесть большее количество часов");
    }

    Time result;
    result.fromSeconds(currentSeconds - subtractSeconds);
    return result;
}

// Дружественная функция: double + Time
Time operator+(double hoursToAdd, const Time& time) {
    return time + hoursToAdd; // Используем уже реализованный оператор
}

// Дружественная функция: double - Time
Time operator-(double hoursToSubtract, const Time& time) {
    int subtractSeconds = static_cast<int>(hoursToSubtract * 3600);
    int timeSeconds = time.toSeconds();

    if (subtractSeconds < timeSeconds) {
        throw invalid_argument("Результат не может быть отрицательным");
    }

    Time result;
    result.fromSeconds(subtractSeconds - timeSeconds);
    return result;
}

// Перегрузка операторов сравнения
bool Time::operator==(const Time& other) const {
    return toSeconds() == other.toSeconds();
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    return toSeconds() < other.toSeconds();
}

bool Time::operator>(const Time& other) const {
    return toSeconds() > other.toSeconds();
}

bool Time::operator<=(const Time& other) const {
    return toSeconds() <= other.toSeconds();
}

bool Time::operator>=(const Time& other) const {
    return toSeconds() >= other.toSeconds();
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << setfill('0') << setw(2) << time.hours << ":"
        << setfill('0') << setw(2) << time.minutes << ":"
        << setfill('0') << setw(2) << time.seconds;
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, Time& time) {
    char delimiter;
    is >> time.hours >> delimiter >> time.minutes >> delimiter >> time.seconds;
    time.normalize();
    return is;
}

// Операторы присваивания
Time& Time::operator+=(const Time& other) {
    *this = *this + other;
    return *this;
}

Time& Time::operator-=(const Time& other) {
    *this = *this - other;
    return *this;
}

// Преобразование Time в double (часы)
Time::operator double() const {
    return hours + minutes / 60.0 + seconds / 3600.0;
}

// Преобразование Time в int (секунды)
Time::operator int() const {
    return toSeconds();
}
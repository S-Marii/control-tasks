#include "safe_time.h"
#include <iomanip>
#include <cmath>

using namespace std;

// Конструктор по умолчанию
SafeTime::SafeTime() : hours_(0), minutes_(0), seconds_(0) {
    // Убрали вывод для уменьшения шума
}

// Конструктор с параметрами (ИСПРАВЛЕННЫЙ)
SafeTime::SafeTime(int h, int m, int s) : hours_(h), minutes_(m), seconds_(s) {
    // Сначала нормализуем, потом проверяем
    normalize();
    validateTime(hours_, minutes_, seconds_);
    cout << "Создано время: ";
    display();
}

// Конструктор копирования
SafeTime::SafeTime(const SafeTime& other)
    : hours_(other.hours_), minutes_(other.minutes_), seconds_(other.seconds_) {
    // Убрали вывод для уменьшения шума
}

// Конструктор перемещения
SafeTime::SafeTime(SafeTime&& other) noexcept
    : hours_(other.hours_), minutes_(other.minutes_), seconds_(other.seconds_) {
    other.hours_ = 0;
    other.minutes_ = 0;
    other.seconds_ = 0;
    // Убрали вывод для уменьшения шума
}

// Оператор присваивания копированием
SafeTime& SafeTime::operator=(const SafeTime& other) {
    if (this != &other) {
        hours_ = other.hours_;
        minutes_ = other.minutes_;
        seconds_ = other.seconds_;
    }
    return *this;
}

// Оператор присваивания перемещением
SafeTime& SafeTime::operator=(SafeTime&& other) noexcept {
    if (this != &other) {
        hours_ = other.hours_;
        minutes_ = other.minutes_;
        seconds_ = other.seconds_;
        other.hours_ = 0;
        other.minutes_ = 0;
        other.seconds_ = 0;
    }
    return *this;
}

// Деструктор
SafeTime::~SafeTime() {
    // Убрали вывод для уменьшения шума
}

// Проверка корректности времени (ИСПРАВЛЕННАЯ)
void SafeTime::validateTime(int h, int m, int s) const {
    if (h < 0 || m < 0 || s < 0) {
        throw InvalidTimeError("Время не может быть отрицательным", h, m, s);
    }

    // После нормализации минуты и секунды всегда < 60
    // Убираем эту проверку или оставляем только для начальных значений
    if (m >= 60 || s >= 60) {
        throw InvalidTimeError("Минуты и секунды должны быть меньше 60", h, m, s);
    }

    if (h >= 24) {
        throw InvalidTimeError("Часы должны быть меньше 24", h, m, s);
    }
}

// Проверка неотрицательности
void SafeTime::validateNonNegative() const {
    if (hours_ < 0 || minutes_ < 0 || seconds_ < 0) {
        throw TimeOperationError("Время не может быть отрицательным", "операция с временем");
    }
}

// Нормализация времени (УЛУЧШЕННАЯ)
void SafeTime::normalize() {
    // Обработка секунд
    if (seconds_ >= 60) {
        minutes_ += seconds_ / 60;
        seconds_ %= 60;
    }
    else if (seconds_ < 0) {
        int borrow = (-seconds_ + 59) / 60;
        minutes_ -= borrow;
        seconds_ += borrow * 60;
    }

    // Обработка минут
    if (minutes_ >= 60) {
        hours_ += minutes_ / 60;
        minutes_ %= 60;
    }
    else if (minutes_ < 0) {
        int borrow = (-minutes_ + 59) / 60;
        hours_ -= borrow;
        minutes_ += borrow * 60;
    }

    // Обработка часов
    if (hours_ >= 24) {
        hours_ %= 24;
    }
    else if (hours_ < 0) {
        // Для времени допускаем отрицательные значения
        hours_ = hours_;
    }
}

// Статическая проверка времени (ИСПРАВЛЕННАЯ)
bool SafeTime::isValidTime(int h, int m, int s) {
    return (h >= 0) && (m >= 0) && (s >= 0);
    // Убрали проверки на < 60, так как normalize обработает это
}

// Проверка текущего времени
bool SafeTime::isValidTime() const {
    return isValidTime(hours_, minutes_, seconds_);
}

// Установка часов
void SafeTime::setHours(int h) {
    // Создаем временный объект для проверки
    SafeTime temp(h, minutes_, seconds_);
    hours_ = h;
    minutes_ = temp.minutes_;
    seconds_ = temp.seconds_;
    cout << "Установлены часы: " << h << endl;
}

// Установка минут
void SafeTime::setMinutes(int m) {
    SafeTime temp(hours_, m, seconds_);
    hours_ = temp.hours_;
    minutes_ = m;
    seconds_ = temp.seconds_;
    cout << "Установлены минуты: " << m << endl;
}

// Установка секунд
void SafeTime::setSeconds(int s) {
    SafeTime temp(hours_, minutes_, s);
    hours_ = temp.hours_;
    minutes_ = temp.minutes_;
    seconds_ = s;
    cout << "Установлены секунды: " << s << endl;
}

// Установка всего времени
void SafeTime::setTime(int h, int m, int s) {
    SafeTime temp(h, m, s);
    hours_ = temp.hours_;
    minutes_ = temp.minutes_;
    seconds_ = temp.seconds_;
    cout << "Установлено время: ";
    display();
}

// Вывод времени
void SafeTime::display() const {
    cout << setfill('0') << setw(2) << hours_ << ":"
        << setfill('0') << setw(2) << minutes_ << ":"
        << setfill('0') << setw(2) << seconds_ << endl;
}

// Вывод времени с меткой
void SafeTime::display(const std::string& label) const {
    cout << label << ": "
        << setfill('0') << setw(2) << hours_ << ":"
        << setfill('0') << setw(2) << minutes_ << ":"
        << setfill('0') << setw(2) << seconds_ << endl;
}

// Преобразование в секунды
int SafeTime::toSeconds() const {
    validateNonNegative();
    return hours_ * 3600 + minutes_ * 60 + seconds_;
}

// Преобразование из секунд
void SafeTime::fromSeconds(int totalSeconds) {
    if (totalSeconds < 0) {
        throw TimeOperationError("Нельзя преобразовать отрицательное количество секунд", "fromSeconds");
    }

    hours_ = totalSeconds / 3600;
    minutes_ = (totalSeconds % 3600) / 60;
    seconds_ = totalSeconds % 60;
    normalize();
}

// Оператор сложения (ИСПРАВЛЕННЫЙ)
SafeTime SafeTime::operator+(const SafeTime& other) const {
    // Создаем объект без проверки в конструкторе
    SafeTime result;
    result.hours_ = hours_ + other.hours_;
    result.minutes_ = minutes_ + other.minutes_;
    result.seconds_ = seconds_ + other.seconds_;
    result.normalize();

    // Проверяем после нормализации
    result.validateNonNegative();
    return result;
}

// Оператор вычитания (ИСПРАВЛЕННЫЙ)
SafeTime SafeTime::operator-(const SafeTime& other) const {
    int totalSeconds1 = toSeconds();
    int totalSeconds2 = other.toSeconds();

    if (totalSeconds1 < totalSeconds2) {
        throw TimeOperationError("Попытка вычесть большее время из меньшего", "operator-");
    }

    SafeTime result;
    result.fromSeconds(totalSeconds1 - totalSeconds2);
    return result;
}

// Оператор += (ИСПРАВЛЕННЫЙ)
SafeTime& SafeTime::operator+=(const SafeTime& other) {
    hours_ += other.hours_;
    minutes_ += other.minutes_;
    seconds_ += other.seconds_;
    normalize();
    validateNonNegative();
    return *this;
}

// Оператор -= (ИСПРАВЛЕННЫЙ)
SafeTime& SafeTime::operator-=(const SafeTime& other) {
    int totalSeconds1 = toSeconds();
    int totalSeconds2 = other.toSeconds();

    if (totalSeconds1 < totalSeconds2) {
        throw TimeOperationError("Попытка вычесть большее время из меньшего", "operator-=");
    }

    fromSeconds(totalSeconds1 - totalSeconds2);
    return *this;
}

// Операторы сравнения
bool SafeTime::operator==(const SafeTime& other) const {
    return toSeconds() == other.toSeconds();
}

bool SafeTime::operator!=(const SafeTime& other) const {
    return !(*this == other);
}

bool SafeTime::operator<(const SafeTime& other) const {
    return toSeconds() < other.toSeconds();
}

bool SafeTime::operator>(const SafeTime& other) const {
    return toSeconds() > other.toSeconds();
}
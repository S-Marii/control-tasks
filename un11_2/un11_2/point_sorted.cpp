#include "point_sorted.h"
#include <iomanip>

using namespace std;

// Конструктор по умолчанию
Point::Point() : x(0), y(0) {}

// Конструктор с параметрами
Point::Point(double x, double y) : x(x), y(y) {}

// Деструктор
Point::~Point() {
    // Деструктор пустой, так как нет динамической памяти
}

// Расстояние до центра координат
double Point::distanceToOrigin() const {
    return sqrt(x * x + y * y);
}

// Вывод точки
void Point::display() const {
    cout << *this;
}

// Перегрузка оператора < для сортировки по расстоянию до центра
bool Point::operator<(const Point& other) const {
    return distanceToOrigin() < other.distanceToOrigin();
}

// Перегрузка оператора >
bool Point::operator>(const Point& other) const {
    return distanceToOrigin() > other.distanceToOrigin();
}

// Перегрузка оператора <=
bool Point::operator<=(const Point& other) const {
    return distanceToOrigin() <= other.distanceToOrigin();
}

// Перегрузка оператора >=
bool Point::operator>=(const Point& other) const {
    return distanceToOrigin() >= other.distanceToOrigin();
}

// Перегрузка оператора ==
bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

// Перегрузка оператора !=
bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << fixed << setprecision(2);
    os << "Point(" << point.x << ", " << point.y << ")";
    os << " [distance: " << point.distanceToOrigin() << "]";
    return os;
}
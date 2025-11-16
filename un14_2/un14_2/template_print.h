#pragma once
#include <iostream>
#include <concepts>
#include <vector>
#include <list>
#include <set>

// Концепт для проверки, что тип можно выводить в поток
template<typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};

// Концепт для проверки, что контейнер можно итерировать
template<typename Container>
concept IterableContainer = requires(Container container) {
    requires Printable<typename Container::value_type>;
container.begin();
container.end();
};

// Шаблонная функция для вывода элементов контейнера
template<IterableContainer Container>
void Print(const Container& container, const std::string& delimiter = ", ") {
    bool first = true;
    for (const auto& element : container) {
        if (!first) {
            std::cout << delimiter;
        }
        std::cout << element;
        first = false;
    }
    std::cout << "\n";
}

// Перегрузка для C-массивов
template<Printable T, size_t N>
void Print(const T(&arr)[N], const std::string& delimiter = ", ") {
    bool first = true;
    for (size_t i = 0; i < N; ++i) {
        if (!first) {
            std::cout << delimiter;
        }
        std::cout << arr[i];
        first = false;
    }
    std::cout << "\n";
}
#pragma once
#include <iostream>
#include <concepts>
#include <vector>
#include <list>
#include <complex>
#include <string>
#include <iterator>

// Пользовательский концепт для сортируемых типов
template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

// Шаблонная функция для проверки отсортированности контейнера
template<Sortable T>
bool is_sorted(const T& container) {
    if (container.empty()) return true;

    auto it = container.begin();
    auto prev = it;
    ++it;

    while (it != container.end()) {
        if (*it < *prev) {
            return false;
        }
        prev = it;
        ++it;
    }
    return true;
}

// Перегрузка для итераторов
template<std::forward_iterator Iterator>
    requires Sortable<typename std::iterator_traits<Iterator>::value_type>
bool is_sorted(Iterator begin, Iterator end) {
    if (begin == end) return true;

    Iterator prev = begin;
    Iterator current = begin;
    ++current;

    while (current != end) {
        if (*current < *prev) {
            return false;
        }
        prev = current;
        ++current;
    }
    return true;
}

// Вспомогательная функция для вывода результата проверки
template<typename Container>
void print_sorted_status(const Container& container, const std::string& name) {
    std::cout << name << ": ";
    if (is_sorted(container)) {
        std::cout << "ОТСОРТИРОВАН";
    }
    else {
        std::cout << "НЕ ОТСОРТИРОВАН";
    }
    std::cout << std::endl;
}

// Функция для вывода контейнера с его статусом сортировки
template<typename Container>
void print_container_with_status(const Container& container, const std::string& name) {
    std::cout << name << " = [";
    bool first = true;
    for (const auto& element : container) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << element;
        first = false;
    }
    std::cout << "] - ";
    if (is_sorted(container)) {
        std::cout << "ОТСОРТИРОВАН";
    }
    else {
        std::cout << "НЕ ОТСОРТИРОВАН";
    }
    std::cout << std::endl;
}
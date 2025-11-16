#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class StudentGrades {
private:
    std::map<std::string, char> grades;

public:
    // Доб/изм оценки студента
    void addGrade(const std::string& studentName, char grade) {
        // Проверка корректности оценки
        if (grade < 'A' || grade > 'F') {
            throw std::invalid_argument("Оценка должна быть в диапазоне A-F");
        }
        grades[studentName] = grade;
    }

    // Получение оценки студента
    char getGrade(const std::string& studentName) const {
        auto it = grades.find(studentName);
        if (it == grades.end()) {
            throw std::runtime_error("Студент " + studentName + " не найден");
        }
        return it->second;
    }

    // Удаление студента
    bool removeStudent(const std::string& studentName) {
        return grades.erase(studentName) > 0;
    }

    // Проверка наличия студента
    bool containsStudent(const std::string& studentName) const {
        return grades.find(studentName) != grades.end();
    }

    // Получение количества студентов
    size_t getStudentCount() const {
        return grades.size();
    }

    // Вывод всех студентов и их оценок
    void displayAllGrades() const {
        if (grades.empty()) {
            std::cout << "Нет студентов в системе." << std::endl;
            return;
        }

        std::cout << "=== ОЦЕНКИ СТУДЕНТОВ ===" << std::endl;
        for (const auto& pair : grades) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // Получение студентов с определенной оценкой
    std::vector<std::string> getStudentsWithGrade(char grade) const {
        std::vector<std::string> result;
        for (const auto& pair : grades) {
            if (pair.second == grade) {
                result.push_back(pair.first);
            }
        }
        return result;
    }

    // Получение средней оценки
    double getAverageGrade() const {
        if (grades.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        int count = 0;

        for (const auto& pair : grades) {
            // Преобразование буквенной оценки в числовую
            switch (pair.second) {
            case 'A': sum += 5.0; break;
            case 'B': sum += 4.0; break;
            case 'C': sum += 3.0; break;
            case 'D': sum += 2.0; break;
            case 'E': sum += 1.0; break;
            case 'F': sum += 0.0; break;
            }
            count++;
        }

        return sum / count;
    }

    // Получение всех имен студентов
    std::vector<std::string> getAllStudentNames() const {
        std::vector<std::string> names;
        for (const auto& pair : grades) {
            names.push_back(pair.first);
        }
        return names;
    }

    // Получение всех пар имя-оценка
    std::vector<std::pair<std::string, char>> getAllStudentGrades() const {
        std::vector<std::pair<std::string, char>> result;
        for (const auto& pair : grades) {
            result.push_back(pair);
        }
        return result;
    }

    // Очистка всех данных
    void clearAll() {
        grades.clear();
    }

    // Статистика по оценкам
    void displayGradeStatistics() const {
        if (grades.empty()) {
            std::cout << "Нет данных для статистики." << std::endl;
            return;
        }

        std::map<char, int> gradeCount;
        for (const auto& pair : grades) {
            gradeCount[pair.second]++;
        }

        std::cout << "=== СТАТИСТИКА ОЦЕНОК ===" << std::endl;
        for (char grade = 'A'; grade <= 'F'; grade++) {
            if (gradeCount.find(grade) != gradeCount.end()) {
                std::cout << "Оценка " << grade << ": " << gradeCount[grade]
                    << " студентов" << std::endl;
            }
        }
        std::cout << "Средний балл: " << getAverageGrade() << std::endl;
    }
};
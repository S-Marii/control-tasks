#include <iostream>
#include <windows.h>
#include "student_grades.h"

using namespace std;

void demonstrateStudentGrades() {
    cout << "=== СИСТЕМА УЧЕТА ОЦЕНОК СТУДЕНТОВ (map) ===\n" << endl;

    StudentGrades gradesSystem;

    // 1. Добавление оценок
    cout << "1. Добавление оценок студентов:" << endl;
    cout << "================================" << endl;

    gradesSystem.addGrade("Иван Петров", 'A');
    gradesSystem.addGrade("Мария Сидорова", 'B');
    gradesSystem.addGrade("Алексей Козлов", 'C');
    gradesSystem.addGrade("Елена Иванова", 'A');
    gradesSystem.addGrade("Дмитрий Смирнов", 'D');
    gradesSystem.addGrade("Ольга Николаева", 'B');

    gradesSystem.displayAllGrades();

    // 2. Получение и изменение оценок
    cout << "\n2. Работа с конкретными студентами:" << endl;
    cout << "=================================" << endl;

    try {
        cout << "Оценка Ивана Петрова: " << gradesSystem.getGrade("Иван Петров") << endl;

        // Изменение оценки
        gradesSystem.addGrade("Иван Петров", 'B');
        cout << "Новая оценка Ивана Петрова: " << gradesSystem.getGrade("Иван Петров") << endl;

        // Попытка получить оценку несуществующего студента
        cout << "Оценка Неизвестного Студента: ";
        cout << gradesSystem.getGrade("Неизвестный Студент") << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    // 3. Поиск студентов по оценкам
    cout << "\n3. Студенты с оценкой A:" << endl;
    cout << "======================" << endl;

    auto aStudents = gradesSystem.getStudentsWithGrade('A');
    if (!aStudents.empty()) {
        for (const auto& name : aStudents) {
            cout << "- " << name << endl;
        }
    }
    else {
        cout << "Студентов с оценкой A нет." << endl;
    }

    // 4. Статистика
    cout << "\n4. Статистика:" << endl;
    cout << "=============" << endl;
    gradesSystem.displayGradeStatistics();

    // 5. Удаление студента
    cout << "\n5. Удаление студента:" << endl;
    cout << "===================" << endl;

    cout << "До удаления: " << gradesSystem.getStudentCount() << " студентов" << endl;
    gradesSystem.removeStudent("Дмитрий Смирнов");
    cout << "После удаления: " << gradesSystem.getStudentCount() << " студентов" << endl;

    gradesSystem.displayAllGrades();
}

void demonstrateAdvancedFeatures() {
    cout << "\n=== РАСШИРЕННЫЕ ВОЗМОЖНОСТИ ===\n" << endl;

    StudentGrades advancedSystem;

    // Добавление группы студентов
    vector<pair<string, char>> studentsData = {
        {"Анна Ковалева", 'A'},
        {"Петр Орлов", 'C'},
        {"Сергей Васильев", 'B'},
        {"Наталья Захарова", 'A'},
        {"Михаил Павлов", 'D'},
        {"Екатерина Федорова", 'B'},
        {"Андрей Морозов", 'F'}
    };

    for (const auto& student : studentsData) {
        advancedSystem.addGrade(student.first, student.second);
    }

    // Демонстрация различных операций
    cout << "1. Все студенты:" << endl;
    advancedSystem.displayAllGrades();

    cout << "\n2. Статистика:" << endl;
    advancedSystem.displayGradeStatistics();

    cout << "\n3. Студенты, нуждающиеся в улучшении (оценки D и F):" << endl;
    auto dStudents = advancedSystem.getStudentsWithGrade('D');
    auto fStudents = advancedSystem.getStudentsWithGrade('F');

    if (!dStudents.empty() || !fStudents.empty()) {
        for (const auto& name : dStudents) {
            cout << "- " << name << " (оценка D)" << endl;
        }
        for (const auto& name : fStudents) {
            cout << "- " << name << " (оценка F)" << endl;
        }
    }
    else {
        cout << "Все студенты успешны!" << endl;
    }

    // Демонстрация structured binding с вектором пар
    cout << "\n4. Использование structured binding:" << endl;
    cout << "===================================" << endl;

    auto allGrades = advancedSystem.getAllStudentGrades();
    for (const auto& [name, grade] : allGrades) {
        cout << "Студент: " << name << ", Оценка: " << grade << endl;
    }
}

void testErrorHandling() {
    cout << "\n=== ОБРАБОТКА ОШИБОК ===\n" << endl;

    StudentGrades testSystem;

    try {
        // Попытка добавить некорректную оценку
        cout << "1. Попытка добавить некорректную оценку:" << endl;
        testSystem.addGrade("Тест Студент", 'X');
    }
    catch (const exception& e) {
        cout << "Перехвачена ошибка: " << e.what() << endl;
    }

    try {
        // Попытка получить оценку несуществующего студента
        cout << "\n2. Попытка получить оценку несуществующего студента:" << endl;
        testSystem.getGrade("Неизвестный");
    }
    catch (const exception& e) {
        cout << "Перехвачена ошибка: " << e.what() << endl;
    }

    // Корректные операции
    cout << "\n3. Корректные операции:" << endl;
    testSystem.addGrade("Корректный Студент", 'B');
    cout << "Оценка добавлена успешно." << endl;
}

void demonstrateMapOperations() {
    cout << "\n=== ОПЕРАЦИИ С MAP ===\n" << endl;

    StudentGrades mapDemo;

    // Добавляем студентов
    mapDemo.addGrade("Иван Иванов", 'A');
    mapDemo.addGrade("Петр Петров", 'B');
    mapDemo.addGrade("Сидор Сидоров", 'C');
    mapDemo.addGrade("Анна Аннова", 'A');

    cout << "1. Итерация по map с использованием auto:" << endl;
    auto allGrades = mapDemo.getAllStudentGrades();
    for (const auto& item : allGrades) {
        cout << item.first << ": " << item.second << endl;
    }

    cout << "\n2. Поиск студентов:" << endl;
    string searchName = "Петр Петров";
    if (mapDemo.containsStudent(searchName)) {
        cout << "Студент " << searchName << " найден, оценка: "
            << mapDemo.getGrade(searchName) << endl;
    }
    else {
        cout << "Студент " << searchName << " не найден" << endl;
    }

    cout << "\n3. Обновление оценки:" << endl;
    mapDemo.addGrade("Петр Петров", 'A');
    cout << "Новая оценка Петра Петрова: " << mapDemo.getGrade("Петр Петров") << endl;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateStudentGrades();
    demonstrateAdvancedFeatures();
    testErrorHandling();
    demonstrateMapOperations();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
#include <iostream>
#include <windows.h>
#include <memory>
#include "education_system.h"

using namespace std;

void demonstrateEducationSystem() {
    cout << "=== СИСТЕМА УЧЕБНОГО ЦЕНТРА - ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ===\n" << endl;
        
    EducationCenter center;

    // 1. Добавление студентов
    auto student1 = make_unique<Student>("Иван Петров", 20, "ST001", 4.5);
    auto student2 = make_unique<Student>("Мария Сидорова", 19, "ST002", 4.2);
    auto student3 = make_unique<Student>("Алексей Козлов", 21, "ST003", 3.8);

    dynamic_cast<Student*>(student1.get())->addCourse("Математика");
    dynamic_cast<Student*>(student1.get())->addCourse("Программирование");
    dynamic_cast<Student*>(student2.get())->addCourse("Физика");
    dynamic_cast<Student*>(student3.get())->addCourse("История");

    center.addPerson(move(student1));
    center.addPerson(move(student2));
    center.addPerson(move(student3));

    // 2. Добавление преподавателей
    auto teacher1 = make_unique<Teacher>("Дмитрий Иванов", 45, "Информатика", 15);
    auto teacher2 = make_unique<Teacher>("Елена Смирнова", 38, "Математика", 12);

    dynamic_cast<Teacher*>(teacher1.get())->addSubject("C++");
    dynamic_cast<Teacher*>(teacher1.get())->addSubject("Алгоритмы");
    dynamic_cast<Teacher*>(teacher2.get())->addSubject("Линейная алгебра");
    dynamic_cast<Teacher*>(teacher2.get())->addSubject("Математический анализ");

    center.addPerson(move(teacher1));
    center.addPerson(move(teacher2));

    // 3. Добавление администраторов
    auto admin1 = make_unique<Administrator>("Ольга Николаева", 35, "Директор");
    auto admin2 = make_unique<Administrator>("Сергей Васильев", 28, "Менеджер");

    dynamic_cast<Administrator*>(admin1.get())->addResponsibility("Общее руководство");
    dynamic_cast<Administrator*>(admin1.get())->addResponsibility("Бюджетирование");
    dynamic_cast<Administrator*>(admin2.get())->addResponsibility("Расписание");
    dynamic_cast<Administrator*>(admin2.get())->addResponsibility("Прием студентов");

    center.addPerson(move(admin1));
    center.addPerson(move(admin2));

    // 4. Демонстрация полиморфизма
    center.displayAllInfo();
    center.demonstratePolymorphism();
    center.calculatePerformanceStats();
    center.displayRTTIInfo();
}

void demonstrateDynamicFeatures() {
    cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ВОЗМОЖНОСТИ СИСТЕМЫ ===\n" << endl;

    vector<unique_ptr<Person>> people;

    // Создание разнородной коллекции
    people.push_back(make_unique<Student>("Анна Ковалева", 22, "ST004", 4.7));
    people.push_back(make_unique<Teacher>("Петр Орлов", 50, "Физика", 25));
    people.push_back(make_unique<Administrator>("Наталья Захарова", 40, "Завуч"));

    // Демонстрация dynamic_cast
    cout << "Использование dynamic_cast для специфических операций:" << endl;
    cout << "=====================================================" << endl;

    for (auto& person : people) {
        cout << "\nОбработка: " << person->getName() << " (" << person->getRole() << ")" << endl;

        if (auto student = dynamic_cast<Student*>(person.get())) {
            student->addCourse("Дополнительный курс");
            student->displayCourses();
            student->setAverageGrade(student->getAverageGrade() + 0.1);
            cout << "Обновленный средний балл: " << student->getAverageGrade() << endl;
        }
        else if (auto teacher = dynamic_cast<Teacher*>(person.get())) {
            teacher->addSubject("Современные технологии");
            teacher->displaySubjects();
            cout << "Стаж работы: " << teacher->getYearsOfExperience() << " лет" << endl;
        }
        else if (auto admin = dynamic_cast<Administrator*>(person.get())) {
            admin->addResponsibility("Координация мероприятий");
            admin->displayResponsibilities();
            cout << "Должность: " << admin->getPosition() << endl;
        }
    }

    // Группировка по ролям
    cout << "\nСтатистика по ролям:" << endl;
    cout << "====================" << endl;

    int studentCount = 0, teacherCount = 0, adminCount = 0;
    for (const auto& person : people) {
        if (person->getRole() == "Student") studentCount++;
        else if (person->getRole() == "Teacher") teacherCount++;
        else if (person->getRole() == "Administrator") adminCount++;
    }

    cout << "Студентов: " << studentCount << endl;
    cout << "Преподавателей: " << teacherCount << endl;
    cout << "Администраторов: " << adminCount << endl;
    cout << "Всего людей: " << people.size() << endl;
}

void testPerformanceCalculation() {
    cout << "\n=== ТЕСТИРОВАНИЕ РАСЧЕТА ПРОИЗВОДИТЕЛЬНОСТИ ===\n" << endl;

    EducationCenter testCenter;

    // Создание тестовых данных
    testCenter.addPerson(make_unique<Student>("Тест Студент", 20, "TEST001", 4.0));
    testCenter.addPerson(make_unique<Teacher>("Тест Преподаватель", 40, "Тестовая", 10));
    testCenter.addPerson(make_unique<Administrator>("Тест Админ", 30, "Тестер"));

    testCenter.calculatePerformanceStats();
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateEducationSystem();
    demonstrateDynamicFeatures();
    testPerformanceCalculation();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
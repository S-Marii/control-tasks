#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>

class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& name = "", int age = 0) : name(name), age(age) {}

    virtual ~Person() = default;

    // Виртуальные методы
    virtual void displayInfo() const {
        std::cout << "Имя: " << name << ", Возраст: " << age;
    }

    virtual void study() const = 0;
    virtual std::string getRole() const = 0;

    virtual double calculatePerformance() const {
        return 0.0;
    }

    // Методы доступа
    std::string getName() const { return name; }
    int getAge() const { return age; }
    void setName(const std::string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
};

class Student : public Person {
private:
    std::string studentId;
    double averageGrade;
    std::vector<std::string> courses;

public:
    Student(const std::string& name = "", int age = 0,
        const std::string& id = "", double avgGrade = 0.0)
        : Person(name, age), studentId(id), averageGrade(avgGrade) {
    }

    void displayInfo() const override {
        Person::displayInfo();
        std::cout << ", ID: " << studentId << ", Средний балл: " << averageGrade;
    }

    void study() const override {
        std::cout << name << " изучает материалы курса" << std::endl;
    }

    std::string getRole() const override {
        return "Student";
    }

    double calculatePerformance() const override {
        return averageGrade;
    }

    void addCourse(const std::string& course) {
        courses.push_back(course);
    }

    void displayCourses() const {
        std::cout << "Курсы студента " << name << ": ";
        for (const auto& course : courses) {
            std::cout << course << " ";
        }
        std::cout << std::endl;
    }
        
    std::string getStudentId() const { return studentId; }
    double getAverageGrade() const { return averageGrade; }
    void setAverageGrade(double grade) { averageGrade = grade; }
};

class Teacher : public Person {
private:
    std::string department;
    std::vector<std::string> subjects;
    int yearsOfExperience;

public:
    Teacher(const std::string& name = "", int age = 0,
        const std::string& dept = "", int experience = 0)
        : Person(name, age), department(dept), yearsOfExperience(experience) {
    }

    void displayInfo() const override {
        Person::displayInfo();
        std::cout << ", Кафедра: " << department
            << ", Опыт: " << yearsOfExperience << " лет";
    }

    void study() const override {
        std::cout << name << " изучает новые методики преподавания" << std::endl;
    }

    std::string getRole() const override {
        return "Teacher";
    }

    double calculatePerformance() const override {
        return yearsOfExperience * 0.1;
    }

    void addSubject(const std::string& subject) {
        subjects.push_back(subject);
    }

    void displaySubjects() const {
        std::cout << "Предметы преподавателя " << name << ": ";
        for (const auto& subject : subjects) {
            std::cout << subject << " ";
        }
        std::cout << std::endl;
    }
        
    std::string getDepartment() const { return department; }
    int getYearsOfExperience() const { return yearsOfExperience; }
};

class Administrator : public Person {
private:
    std::string position;
    std::vector<std::string> responsibilities;

public:
    Administrator(const std::string& name = "", int age = 0,
        const std::string& pos = "")
        : Person(name, age), position(pos) {
    }

    void displayInfo() const override {
        Person::displayInfo();
        std::cout << ", Должность: " << position;
    }

    void study() const override {
        std::cout << name << " изучает административные процедуры" << std::endl;
    }

    std::string getRole() const override {
        return "Administrator";
    }

    double calculatePerformance() const override {
        return 1.0; // Базовая производительность
    }

    void addResponsibility(const std::string& responsibility) {
        responsibilities.push_back(responsibility);
    }

    void displayResponsibilities() const {
        std::cout << "Обязанности администратора " << name << ": ";
        for (const auto& resp : responsibilities) {
            std::cout << resp << " ";
        }
        std::cout << std::endl;
    }
    
    std::string getPosition() const { return position; }
};

// Класс для управления учебным центром
class EducationCenter {
private:
    std::vector<std::unique_ptr<Person>> people;

public:
    void addPerson(std::unique_ptr<Person> person) {
        people.push_back(std::move(person));
    }

    void displayAllInfo() const {
        std::cout << "=== ИНФОРМАЦИЯ О ВСЕХ ЛЮДЯХ В УЧЕБНОМ ЦЕНТРЕ ===" << std::endl;
        for (size_t i = 0; i < people.size(); ++i) {
            std::cout << "[" << (i + 1) << "] ";
            people[i]->displayInfo();
            std::cout << std::endl;
        }
    }

    void demonstratePolymorphism() const {
        std::cout << "\n=== ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ===" << std::endl;
        for (const auto& person : people) {
            std::cout << person->getRole() << " " << person->getName() << ": ";
            person->study();
        }
    }

    void calculatePerformanceStats() const {
        std::cout << "\n=== СТАТИСТИКА ПРОИЗВОДИТЕЛЬНОСТИ ===" << std::endl;
        double totalPerformance = 0.0;

        for (const auto& person : people) {
            double performance = person->calculatePerformance();
            std::cout << person->getName() << " (" << person->getRole()
                << "): " << performance << std::endl;
            totalPerformance += performance;
        }

        std::cout << "Общая производительность: " << totalPerformance << std::endl;
        std::cout << "Средняя производительность: "
            << (people.empty() ? 0 : totalPerformance / people.size()) << std::endl;
    }

    void displayRTTIInfo() const {
        std::cout << "\n=== ИНФОРМАЦИЯ RTTI ===" << std::endl;
        for (const auto& person : people) {
            std::cout << person->getRole() << " " << person->getName()
                << " - RTTI: " << typeid(*person).name() << std::endl;
        }
    }

    size_t getPeopleCount() const {
        return people.size();
    }
};
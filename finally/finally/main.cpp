#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <format>
#include <conio.h>

// Класс адреса (композиция)
class Address {
private:
    std::string street;
    std::string city;
    std::string postalCode;

public:
    Address(const std::string& street, const std::string& city, const std::string& postal)
        : street(street), city(city), postalCode(postal) {
    }

    std::string toString() const {
        return street + ", " + city + ", " + postalCode;
    }

    std::string serialize() const {
        return street + ";" + city + ";" + postalCode;
    }

    static Address deserialize(const std::string& data) {
        std::istringstream ss(data);
        std::string street, city, postal;
        std::getline(ss, street, ';');
        std::getline(ss, city, ';');
        std::getline(ss, postal, ';');
        return Address(street, city, postal);
    }
};

// Абстрактный базовый класс
class Person {
protected:
    std::string firstName;
    std::string lastName;
    std::string phone;

public:
    Person(const std::string& first, const std::string& last, const std::string& phone)
        : firstName(first), lastName(last), phone(phone) {
    }

    virtual ~Person() = default;

    // Абстрактные методы
    virtual std::string getOccupation() const = 0;
    virtual std::string getDetails() const = 0;

    // Общие методы
    virtual std::string getFullName() const {
        return firstName + " " + lastName;
    }

    std::string getPhone() const { return phone; }

    // Виртуальный метод для клонирования (Prototype pattern)
    virtual std::unique_ptr<Person> clone() const = 0;

    // Виртуальный метод для сериализации
    virtual std::string serialize() const = 0;
};

// Класс Студент
class Student : public Person {
private:
    std::string university;
    int course;
    std::string specialization;
    Address address;  // Композиция

public:
    Student(const std::string& first, const std::string& last, const std::string& phone,
        const std::string& uni, int course, const std::string& spec, const Address& addr)
        : Person(first, last, phone), university(uni), course(course),
        specialization(spec), address(addr) {
    }

    std::string getOccupation() const override {
        return "Student";
    }

    std::string getDetails() const override {
        return "University: " + university + ", Course: " + std::to_string(course) +
            ", Specialization: " + specialization + ", Address: " + address.toString();
    }

    std::unique_ptr<Person> clone() const override {
        return std::make_unique<Student>(*this);
    }

    std::string serialize() const override {
        return "Student;" + firstName + ";" + lastName + ";" + phone + ";" +
            university + ";" + std::to_string(course) + ";" + specialization + ";" +
            address.serialize();
    }
};

// Класс Преподаватель
class Teacher : public Person {
private:
    std::string university;
    std::string department;
    std::string academicDegree;
    std::vector<std::string> subjects;  // Агрегация

public:
    Teacher(const std::string& first, const std::string& last, const std::string& phone,
        const std::string& uni, const std::string& dept, const std::string& degree)
        : Person(first, last, phone), university(uni), department(dept), academicDegree(degree) {
    }

    void addSubject(const std::string& subject) {
        subjects.push_back(subject);
    }

    std::string getOccupation() const override {
        return "Teacher";
    }

    std::string getDetails() const override {
        std::string subjectsStr;
        for (const auto& subject : subjects) {
            subjectsStr += subject + ", ";
        }
        if (!subjectsStr.empty()) {
            subjectsStr = subjectsStr.substr(0, subjectsStr.length() - 2);
        }

        return "University: " + university + ", Department: " + department +
            ", Degree: " + academicDegree + ", Subjects: " + subjectsStr;
    }

    std::unique_ptr<Person> clone() const override {
        return std::make_unique<Teacher>(*this);
    }

    std::string serialize() const override {
        std::string subjectsStr;
        for (const auto& subject : subjects) {
            subjectsStr += subject + ",";
        }
        if (!subjectsStr.empty()) {
            subjectsStr.pop_back();
        }

        return "Teacher;" + firstName + ";" + lastName + ";" + phone + ";" +
            university + ";" + department + ";" + academicDegree + ";" + subjectsStr;
    }
};

// Шаблонный репозиторий (Repository pattern + Singleton)
class PersonRepository {
private:
    std::vector<std::unique_ptr<Person>> persons;
    static std::unique_ptr<PersonRepository> instance;

    PersonRepository() = default;

public:
    // Singleton
    static PersonRepository& getInstance() {
        if (!instance) {
            instance = std::unique_ptr<PersonRepository>(new PersonRepository());
        }
        return *instance;
    }

    // Запрет копирования
    PersonRepository(const PersonRepository&) = delete;
    PersonRepository& operator=(const PersonRepository&) = delete;

    void addPerson(std::unique_ptr<Person> person) {
        persons.push_back(std::move(person));
    }

    // Iterator pattern
    auto begin() { return persons.begin(); }
    auto end() { return persons.end(); }
    auto begin() const { return persons.begin(); }
    auto end() const { return persons.end(); }

    size_t size() const { return persons.size(); }

    // Поиск по имени (Strategy-like)
    std::vector<Person*> findByName(const std::string& name) {
        std::vector<Person*> result;
        for (const auto& person : persons) {
            if (person->getFullName().find(name) != std::string::npos) {
                result.push_back(person.get());
            }
        }
        return result;
    }

    // Сохранение в файл
    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        for (const auto& person : persons) {
            file << person->serialize() << std::endl;
        }

        file.close();
        return true;
    }

    // Загрузка из файла (Factory Method pattern)
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        persons.clear();
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string type;
            std::getline(ss, type, ';');

            std::unique_ptr<Person> person;
            if (type == "Student") {
                person = createStudentFromStream(ss);
            }
            else if (type == "Teacher") {
                person = createTeacherFromStream(ss);
            }

            if (person) {
                persons.push_back(std::move(person));
            }
        }

        file.close();
        return true;
    }

private:
    std::unique_ptr<Person> createStudentFromStream(std::istringstream& ss) {
        std::string first, last, phone, uni, spec, addrData;
        int course;

        std::getline(ss, first, ';');
        std::getline(ss, last, ';');
        std::getline(ss, phone, ';');
        std::getline(ss, uni, ';');
        ss >> course; ss.ignore();
        std::getline(ss, spec, ';');
        std::getline(ss, addrData);

        Address addr = Address::deserialize(addrData);
        return std::make_unique<Student>(first, last, phone, uni, course, spec, addr);
    }

    std::unique_ptr<Person> createTeacherFromStream(std::istringstream& ss) {
        std::string first, last, phone, uni, dept, degree, subjectsStr;

        std::getline(ss, first, ';');
        std::getline(ss, last, ';');
        std::getline(ss, phone, ';');
        std::getline(ss, uni, ';');
        std::getline(ss, dept, ';');
        std::getline(ss, degree, ';');
        std::getline(ss, subjectsStr);

        auto teacher = std::make_unique<Teacher>(first, last, phone, uni, dept, degree);

        std::istringstream subjectsStream(subjectsStr);
        std::string subject;
        while (std::getline(subjectsStream, subject, ',')) {
            if (!subject.empty()) {
                teacher->addSubject(subject);
            }
        }

        return teacher;
    }
};

// Инициализация статического члена
std::unique_ptr<PersonRepository> PersonRepository::instance = nullptr;

// Базовый класс команды (Command pattern)
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual std::string getDescription() const = 0;
};

// Конкретные команды
class AddStudentCommand : public Command {
public:
    void execute() override {
        std::string first, last, phone, uni, spec, street, city, postal;
        int course;

        std::cout << "Adding Student:\n";
        std::cout << "First Name: "; std::cin >> first;
        std::cout << "Last Name: "; std::cin >> last;
        std::cout << "Phone: "; std::cin >> phone;
        std::cout << "University: "; std::cin >> uni;
        std::cout << "Course: "; std::cin >> course;
        std::cout << "Specialization: "; std::cin >> spec;
        std::cout << "Street: "; std::cin >> street;
        std::cout << "City: "; std::cin >> city;
        std::cout << "Postal Code: "; std::cin >> postal;

        Address addr(street, city, postal);
        auto student = std::make_unique<Student>(first, last, phone, uni, course, spec, addr);
        PersonRepository::getInstance().addPerson(std::move(student));

        std::cout << "Student added successfully!\n";
    }

    std::string getDescription() const override {
        return "Add Student";
    }
};

class AddTeacherCommand : public Command {
public:
    void execute() override {
        std::string first, last, phone, uni, dept, degree;

        std::cout << "Adding Teacher:\n";
        std::cout << "First Name: "; std::cin >> first;
        std::cout << "Last Name: "; std::cin >> last;
        std::cout << "Phone: "; std::cin >> phone;
        std::cout << "University: "; std::cin >> uni;
        std::cout << "Department: "; std::cin >> dept;
        std::cout << "Academic Degree: "; std::cin >> degree;

        auto teacher = std::make_unique<Teacher>(first, last, phone, uni, dept, degree);

        // Добавление предметов
        std::cout << "Enter subjects (type 'done' to finish):\n";
        std::string subject;
        while (true) {
            std::cout << "Subject: ";
            std::cin >> subject;
            if (subject == "done") break;
            teacher->addSubject(subject);
        }

        PersonRepository::getInstance().addPerson(std::move(teacher));
        std::cout << "Teacher added successfully!\n";
    }

    std::string getDescription() const override {
        return "Add Teacher";
    }
};

class ListPersonsCommand : public Command {
public:
    void execute() override {
        auto& repo = PersonRepository::getInstance();
        std::cout << "\n--- Persons List (" << repo.size() << ") ---\n";

        int index = 1;
        for (const auto& person : repo) {
            std::cout << index++ << ". " << person->getFullName()
                << " (" << person->getOccupation() << ")\n";
            std::cout << "   " << person->getDetails() << "\n";
            std::cout << "   Phone: " << person->getPhone() << "\n\n";
        }
    }

    std::string getDescription() const override {
        return "List All Persons";
    }
};

class SaveToFileCommand : public Command {
public:
    void execute() override {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        if (PersonRepository::getInstance().saveToFile(filename)) {
            std::cout << "Data saved successfully!\n";
        }
        else {
            std::cout << "Error saving data!\n";
        }
    }

    std::string getDescription() const override {
        return "Save to File";
    }
};

class LoadFromFileCommand : public Command {
public:
    void execute() override {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        if (PersonRepository::getInstance().loadFromFile(filename)) {
            std::cout << "Data loaded successfully!\n";
        }
        else {
            std::cout << "Error loading data!\n";
        }
    }

    std::string getDescription() const override {
        return "Load from File";
    }
};

// Фасад интерфейса (Facade pattern)
class UserInterface {
private:
    std::vector<std::unique_ptr<Command>> commands;

public:
    UserInterface() {
        // Регистрация команд
        commands.push_back(std::make_unique<AddStudentCommand>());
        commands.push_back(std::make_unique<AddTeacherCommand>());
        commands.push_back(std::make_unique<ListPersonsCommand>());
        commands.push_back(std::make_unique<SaveToFileCommand>());
        commands.push_back(std::make_unique<LoadFromFileCommand>());
    }

    void run() {
        while (true) {
            showMenu();
            int choice = getChoice();

            if (choice == 0) break;

            if (choice > 0 && choice <= static_cast<int>(commands.size())) {
                commands[choice - 1]->execute();
            }
            else {
                std::cout << "Invalid choice!\n";
            }

            std::cout << "Press any key to continue...";
            _getch();
        }
    }

private:
    void showMenu() {
        system("cls");
        std::cout << "=== Person Management System ===\n";
        std::cout << "0. Exit\n";

        for (size_t i = 0; i < commands.size(); ++i) {
            std::cout << i + 1 << ". " << commands[i]->getDescription() << "\n";
        }

        std::cout << "Choose option: ";
    }

    int getChoice() {
        int choice;
        std::cin >> choice;
        return choice;
    }
};

int main() {
    // тестовые данные
    auto& repo = PersonRepository::getInstance();

    Address addr1("Main St 123", "New York", "10001");
    auto student1 = std::make_unique<Student>("John", "Doe", "+123456789",
        "NYU", 2, "Computer Science", addr1);
    repo.addPerson(std::move(student1));

    auto teacher1 = std::make_unique<Teacher>("Alice", "Smith", "+987654321",
        "NYU", "Computer Science", "PhD");
    teacher1->addSubject("Algorithms");
    teacher1->addSubject("Data Structures");
    repo.addPerson(std::move(teacher1));

    // Запуск интерфейса
    UserInterface ui;
    ui.run();

    return 0;
}
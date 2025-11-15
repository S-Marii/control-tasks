#include <iostream>
#include <windows.h>
#include <vector>
#include <memory>
#include <algorithm>
#include "vehicles.h"

using namespace std;

void demonstrateVehicles() {
    cout << "=== ДЕМОНСТРАЦИЯ ИЕРАРХИИ ТРАНСПОРТНЫХ СРЕДСТВ ===\n" << endl;

    // 1. Создание вектора умных указателей на Vehicle
    vector<unique_ptr<Vehicle>> vehicles;

    // 2. Добавление различных транспортных средств
    vehicles.push_back(make_unique<Car>());
    vehicles.push_back(make_unique<Boat>());
    vehicles.push_back(make_unique<Plane>());
    vehicles.push_back(make_unique<AmphibiousVehicle>(true)); // На земле
    vehicles.push_back(make_unique<AmphibiousVehicle>(false)); // На воде

    // 3. Демонстрация полиморфного поведения
    cout << "1. Полиморфное поведение транспортных средств:" << endl;
    cout << "==============================================" << endl;

    for (const auto& vehicle : vehicles) {
        cout << vehicle->type() << ": ";
        vehicle->move();
    }

    // 4. Демонстрация RTTI
    cout << "\n2. Информация RTTI:" << endl;
    cout << "==================" << endl;

    for (const auto& vehicle : vehicles) {
        cout << vehicle->type() << " - ";
        vehicle->printRTTIInfo();
    }

    // 5. Сериализация в файл
    cout << "\n3. Сериализация в файл:" << endl;
    cout << "======================" << endl;

    ofstream file("vehicles.txt");
    if (file.is_open()) {
        for (const auto& vehicle : vehicles) {
            vehicle->serialize(file);
            cout << "Записано: " << vehicle->type() << endl;
        }
        file.close();
        cout << "Данные сохранены в файл 'vehicles.txt'" << endl;
    }

    // 6. Демонстрация работы с амфибийным транспортным средством
    cout << "\n4. Демонстрация AmphibiousVehicle:" << endl;
    cout << "================================" << endl;

    auto amphibious = dynamic_cast<AmphibiousVehicle*>(vehicles[3].get());
    if (amphibious) {
        cout << "Начальное состояние: ";
        amphibious->move();

        amphibious->switchMode();
        cout << "После переключения: ";
        amphibious->move();

        amphibious->switchMode();
        cout << "После обратного переключения: ";
        amphibious->move();
    }

    // 7. Статистика
    cout << "\n5. Статистика:" << endl;
    cout << "==============" << endl;
    cout << "Всего создано транспортных средств: " << Vehicle::getTotalVehicles() << endl;

    // 8. Демонстрация фабрики
    cout << "\n6. Демонстрация фабрики:" << endl;
    cout << "=======================" << endl;

    vector<unique_ptr<Vehicle>> factoryVehicles;
    factoryVehicles.push_back(VehicleFactory::createVehicle("car"));
    factoryVehicles.push_back(VehicleFactory::createVehicle("boat"));
    factoryVehicles.push_back(VehicleFactory::createVehicle("plane"));
    factoryVehicles.push_back(VehicleFactory::createVehicle("amphibious"));

    for (const auto& vehicle : factoryVehicles) {
        if (vehicle) {
            cout << "Фабрика создала: " << vehicle->type() << endl;
        }
    }
}

void demonstrateCollections() {
    cout << "\n=== РАБОТА С КОЛЛЕКЦИЯМИ ТРАНСПОРТНЫХ СРЕДСТВ ===\n" << endl;

    // 1. Создание разнородной коллекции
    vector<unique_ptr<Vehicle>> transportPark;

    // Добавляем различные транспортные средства
    transportPark.push_back(make_unique<Car>());
    transportPark.push_back(make_unique<Car>());
    transportPark.push_back(make_unique<Boat>());
    transportPark.push_back(make_unique<Plane>());
    transportPark.push_back(make_unique<AmphibiousVehicle>());
    transportPark.push_back(make_unique<Plane>());

    // 2. Группировка по типам
    cout << "Состав транспортного парка:" << endl;
    cout << "===========================" << endl;

    int carCount = 0, boatCount = 0, planeCount = 0, amphibiousCount = 0;

    for (const auto& vehicle : transportPark) {
        if (vehicle->type() == "Car") carCount++;
        else if (vehicle->type() == "Boat") boatCount++;
        else if (vehicle->type() == "Plane") planeCount++;
        else if (vehicle->type() == "AmphibiousVehicle") amphibiousCount++;
    }

    cout << "Автомобилей: " << carCount << endl;
    cout << "Лодок: " << boatCount << endl;
    cout << "Самолетов: " << planeCount << endl;
    cout << "Амфибий: " << amphibiousCount << endl;
    cout << "Всего единиц: " << transportPark.size() << endl;

    // 3. Демонстрация полиморфного вызова
    cout << "\nДемонстрация работы транспорта:" << endl;
    cout << "===============================" << endl;

    for (size_t i = 0; i < transportPark.size(); ++i) {
        cout << "Транспорт #" << (i + 1) << " - ";
        transportPark[i]->move();
    }
}

void testDynamicCast() {
    cout << "\n=== ТЕСТИРОВАНИЕ DYNAMIC_CAST ===\n" << endl;

    vector<unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(make_unique<Car>());
    vehicles.push_back(make_unique<Boat>());
    vehicles.push_back(make_unique<Plane>());
    vehicles.push_back(make_unique<AmphibiousVehicle>());

    cout << "Результаты dynamic_cast:" << endl;
    cout << "========================" << endl;

    for (size_t i = 0; i < vehicles.size(); ++i) {
        cout << "Объект #" << (i + 1) << " (" << vehicles[i]->type() << "): ";

        // Попытка приведения к конкретным типам
        if (dynamic_cast<Car*>(vehicles[i].get())) {
            cout << "успешно приведен к Car" << endl;
        }
        else if (dynamic_cast<Boat*>(vehicles[i].get())) {
            cout << "успешно приведен к Boat" << endl;
        }
        else if (dynamic_cast<Plane*>(vehicles[i].get())) {
            cout << "успешно приведен к Plane" << endl;
        }
        else if (dynamic_cast<AmphibiousVehicle*>(vehicles[i].get())) {
            cout << "успешно приведен к AmphibiousVehicle" << endl;
        }
        else {
            cout << "не удалось привести к известному типу" << endl;
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateVehicles();
    demonstrateCollections();
    testDynamicCast();

    // Финальная статистика
    cout << "\n=== ФИНАЛЬНАЯ СТАТИСТИКА ===" << endl;
    cout << "Осталось транспортных средств: " << Vehicle::getTotalVehicles() << endl;

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
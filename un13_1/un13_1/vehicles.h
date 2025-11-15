#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <memory>

class Vehicle {
protected:
    static int totalVehicles;

public:
    Vehicle() {
        totalVehicles++;
    }

    // Чисто виртуальные методы
    virtual void move() const = 0;
    virtual std::string type() const = 0;

    // Виртуальный деструктор
    virtual ~Vehicle() {
        totalVehicles--;
    }

    // Статический метод для получения количества созданных транспортных средств
    static int getTotalVehicles() {
        return totalVehicles;
    }

    // Виртуальный метод для сериализации
    virtual void serialize(std::ofstream& file) const {
        file << type() << ";" << getBehaviorDescription() << "\n";
    }

    // Метод для получения описания поведения
    virtual std::string getBehaviorDescription() const = 0;

    // Метод для получения информации о типе через RTTI
    virtual void printRTTIInfo() const {
        std::cout << "RTTI type: " << typeid(*this).name() << std::endl;
    }
};

// Инициализация статической переменной
int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
public:
    void move() const override {
        std::cout << "Car is driving on the road." << std::endl;
    }

    std::string type() const override {
        return "Car";
    }

    std::string getBehaviorDescription() const override {
        return "driving on the road";
    }

    ~Car() override = default;
};

class Boat : public Vehicle {
public:
    void move() const override {
        std::cout << "Boat is sailing on water." << std::endl;
    }

    std::string type() const override {
        return "Boat";
    }

    std::string getBehaviorDescription() const override {
        return "sailing on water";
    }

    ~Boat() override = default;
};

class Plane : public Vehicle {
public:
    void move() const override {
        std::cout << "Plane is flying in the sky." << std::endl;
    }

    std::string type() const override {
        return "Plane";
    }

    std::string getBehaviorDescription() const override {
        return "flying in the sky";
    }

    ~Plane() override = default;
};

// Амфибийное транспортное средство
class AmphibiousVehicle : public Vehicle {
private:
    bool onLand;

public:
    AmphibiousVehicle(bool startOnLand = true) : onLand(startOnLand) {}

    void move() const override {
        if (onLand) {
            std::cout << "AmphibiousVehicle is driving on the road." << std::endl;
        }
        else {
            std::cout << "AmphibiousVehicle is sailing on water." << std::endl;
        }
    }

    void switchMode() {
        onLand = !onLand;
        std::cout << "Switched to " << (onLand ? "land" : "water") << " mode" << std::endl;
    }

    std::string type() const override {
        return "AmphibiousVehicle";
    }

    std::string getBehaviorDescription() const override {
        return onLand ? "driving on the road" : "sailing on water";
    }

    bool isOnLand() const { return onLand; }

    ~AmphibiousVehicle() override = default;
};

// Фабрика для создания транспортных средств
class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> createVehicle(const std::string& type) {
        if (type == "car") {
            return std::make_unique<Car>();
        }
        else if (type == "boat") {
            return std::make_unique<Boat>();
        }
        else if (type == "plane") {
            return std::make_unique<Plane>();
        }
        else if (type == "amphibious") {
            return std::make_unique<AmphibiousVehicle>();
        }
        return nullptr;
    }
};
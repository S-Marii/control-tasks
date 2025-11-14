#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Функция вывода справки
void printHelp(const char* programName) {
    cout << "Использование:\n";
    cout << "  " << programName << " -a <число1> <число2>  - сложение\n";
    cout << "  " << programName << " -m <число1> <число2>  - умножение\n";
    cout << "  " << programName << " -h                    - справка\n";
}

// Функция проверки корректности числа
bool isValidNumber(const char* str) {
    if (str == nullptr || *str == '\0') return false;

    // Проверка каждого символа
    for (int i = 0; str[i] != '\0'; i++) {
        if (i == 0 && str[i] == '-') continue;
        if (!isdigit(str[i])) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    system("chcp 1251");

    // Проверка количества аргументов
    if (argc == 1) {
        cerr << "Ошибка: не указаны параметры!\n";
        printHelp(argv[0]);
        return 1;
    }

    // Обработка запроса справки
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printHelp(argv[0]);
        return 0;
    }

    // Проверка количества параметров для операций
    if (argc != 4) {
        cerr << "Ошибка: неверное количество параметров!\n";
        printHelp(argv[0]);
        return 1;
    }

    // Проверка флага операции
    if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-m") != 0) {
        cerr << "Ошибка: неверный флаг операции!\n";
        printHelp(argv[0]);
        return 1;
    }

    // Проверка корректности чисел
    if (!isValidNumber(argv[2]) || !isValidNumber(argv[3])) {
        cerr << "Ошибка: неверный формат чисел!\n";
        return 1;
    }

    // Преобразование строк в числа
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);

    // Выполнение операции
    if (strcmp(argv[1], "-a") == 0) {
        cout << "Результат сложения: " << num1 << " + " << num2 << " = " << num1 + num2 << endl;
    }
    else if (strcmp(argv[1], "-m") == 0) {
        cout << "Результат умножения: " << num1 << " * " << num2 << " = " << num1 * num2 << endl;
    }

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

string decimalToBinaryRecursive(int num) {
    if (num == 0) {
        return "0";
    }
    if (num == 1) {
        return "1";
    }
    return decimalToBinaryRecursive(num / 2) + to_string(num % 2);
}

void decimalToBinaryHelper(int num, string& result) {
    if (num > 1) {
        decimalToBinaryHelper(num / 2, result);
    }
    result += to_string(num % 2);
}

string decimalToBinary(int num) {
    if (num == 0) return "0";
    string result;
    decimalToBinaryHelper(num, result);
    return result;
}

string decimalToBinary(int num, bool withPrefix) {
    string binary = decimalToBinary(num);
    if (withPrefix) {
        return "0b" + binary;
    }
    return binary;
}

int main() {
    system("chcp 1251");

    cout << "=== РЕКУРСИВНЫЙ ПЕРЕВОД В ДВОИЧНУЮ СИСТЕМУ ===\n\n";

    int number;
    cout << "Введите целое положительное число: ";
    cin >> number;

    if (number < 0) {
        cout << "Ошибка: число должно быть положительным!" << endl;
        return 1;
    }

    string binary1 = decimalToBinaryRecursive(number);
    string binary2 = decimalToBinary(number);
    string binary3 = decimalToBinary(number, true);

    cout << "\nРезультаты перевода:\n";
    cout << "Рекурсивный метод: " << binary1 << endl;
    cout << "Метод с аккумулятором: " << binary2 << endl;
    cout << "С префиксом: " << binary3 << endl;
       
    cout << "\nДемонстрация для различных чисел:\n";
    int testNumbers[] = { 0, 1, 2, 5, 10, 15, 16, 255, 1024 };

    for (int num : testNumbers) {
        cout << num << " в двоичной: " << decimalToBinary(num, true) << endl;
    }
        
    cout << "\nПроверка преобразований:\n";
    for (int i = 0; i <= 20; i++) {
        cout << i << " -> " << decimalToBinary(i);        
        cout << " (проверка: ";
        int check = stoi(decimalToBinary(i), nullptr, 2);
        cout << check << ")" << endl;
    }

    return 0;
}
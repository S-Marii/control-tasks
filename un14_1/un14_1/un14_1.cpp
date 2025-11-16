#include <iostream>
#include <windows.h>
#include "template_array_functions.h"

using namespace std;

void demonstrateArrayFunctions() {
    cout << "=== ШАБЛОННЫЕ ФУНКЦИИ ДЛЯ РАБОТЫ С МАССИВАМИ ===\n" << endl;

    // 1. Массив int
    cout << "1. Массив int:" << endl;
    int intArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int intSize = sizeof(intArr) / sizeof(intArr[0]);

    cout << "Массив: ";
    printArray(intArr, intSize);
    cout << "Среднее арифметическое: " << calculateAverage(intArr, intSize) << endl;

    // 2. Массив long
    cout << "\n2. Массив long:" << endl;
    long longArr[] = { 100L, 200L, 300L, 400L, 500L };
    int longSize = sizeof(longArr) / sizeof(longArr[0]);

    cout << "Массив: ";
    printArray(longArr, longSize);
    cout << "Среднее арифметическое: " << calculateAverage(longArr, longSize) << endl;

    // 3. Массив double
    cout << "\n3. Массив double:" << endl;
    double doubleArr[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };
    int doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);

    cout << "Массив: ";
    printArray(doubleArr, doubleSize);
    cout << "Среднее арифметическое: " << calculateAverage(doubleArr, doubleSize) << endl;

    // 4. Массив char
    cout << "\n4. Массив char:" << endl;
    char charArr[] = { 'A', 'B', 'C', 'D', 'E' };
    int charSize = sizeof(charArr) / sizeof(charArr[0]);

    cout << "Массив как символы: ";
    printArray(charArr, charSize);

    // Особый случай: char преобразуется в int при вычислении среднего
    cout << "Среднее арифметическое (как int): " << static_cast<int>(calculateAverage(charArr, charSize)) << endl;
    cout << "Среднее арифметическое (как char): '" << static_cast<char>(calculateAverage(charArr, charSize)) << "'" << endl;

    // 5. Строка как массив char
    cout << "\n5. Строка как массив char:" << endl;
    char str[] = "Hello";
    int strSize = sizeof(str) / sizeof(str[0]) - 1; // -1 чтобы исключить нулевой терминатор

    cout << "Строка: ";
    printArray(str, strSize);
    cout << "Среднее арифметическое символов: " << static_cast<int>(calculateAverage(str, strSize)) << endl;

    // 6. Массив с пользовательским разделителем
    cout << "\n6. Массив с пользовательским разделителем:" << endl;
    cout << "Массив: ";
    printArray(intArr, intSize, " | ");
}

void testEdgeCases() {
    cout << "\n=== ТЕСТИРОВАНИЕ ГРАНИЧНЫХ СЛУЧАЕВ ===\n" << endl;

    // 1. Пустой массив - используем указатель и размер 0
    cout << "1. Пустой массив:" << endl;
    int* emptyArr = nullptr;
    cout << "Среднее пустого массива: " << calculateAverage(emptyArr, 0) << endl;
    cout << "Вывод пустого массива: ";
    printArray(emptyArr, 0);

    // 2. Массив из одного элемента
    cout << "\n2. Массив из одного элемента:" << endl;
    double singleArr[] = { 42.5 };
    int singleSize = sizeof(singleArr) / sizeof(singleArr[0]);
    cout << "Массив: ";
    printArray(singleArr, singleSize);
    cout << "Среднее: " << calculateAverage(singleArr, singleSize) << endl;

    // 3. Массив с отрицательными числами
    cout << "\n3. Массив с отрицательными числами:" << endl;
    int negativeArr[] = { -5, -3, -1, 2, 4, 6 };
    int negativeSize = sizeof(negativeArr) / sizeof(negativeArr[0]);

    cout << "Массив: ";
    printArray(negativeArr, negativeSize);
    cout << "Среднее: " << calculateAverage(negativeArr, negativeSize) << endl;

    // 4. Большой массив
    cout << "\n4. Большой массив:" << endl;
    const int bigSize = 100;
    int bigArr[bigSize];
    for (int i = 0; i < bigSize; ++i) {
        bigArr[i] = i + 1;
    }
    cout << "Среднее арифметическое чисел от 1 до 100: " << calculateAverage(bigArr, bigSize) << endl;

    // 5. Массив с нулевыми элементами
    cout << "\n5. Массив с нулевыми элементами:" << endl;
    double zeros[] = { 0.0, 0.0, 0.0, 0.0 };
    int zerosSize = sizeof(zeros) / sizeof(zeros[0]);
    cout << "Массив: ";
    printArray(zeros, zerosSize);
    cout << "Среднее: " << calculateAverage(zeros, zerosSize) << endl;
}

void demonstrateTypeDeduction() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ВЫВОДА ТИПОВ ===\n" << endl;

    // Автоматический вывод типов при вычислении среднего
    short shortArr[] = { 10, 20, 30, 40, 50 };
    int shortSize = sizeof(shortArr) / sizeof(shortArr[0]);

    float floatArr[] = { 1.5f, 2.5f, 3.5f, 4.5f };
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);

    cout << "Массив short: ";
    printArray(shortArr, shortSize);
    auto shortAvg = calculateAverage(shortArr, shortSize);
    cout << "Среднее (тип: " << typeid(shortAvg).name() << "): " << shortAvg << endl;

    cout << "\nМассив float: ";
    printArray(floatArr, floatSize);
    auto floatAvg = calculateAverage(floatArr, floatSize);
    cout << "Среднее (тип: " << typeid(floatAvg).name() << "): " << floatAvg << endl;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    demonstrateArrayFunctions();
    testEdgeCases();
    demonstrateTypeDeduction();

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
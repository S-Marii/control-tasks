#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Функции для работы с массивами (из занятия 5)
void printArray(const int arr[], int size, ostream& stream = cout) {
    for (int i = 0; i < size; i++) {
        stream << setw(4) << arr[i] << " ";
    }
    stream << endl;
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Функция заполнения массива случайными числами
void fillArrayRandom(int arr[], int size, int minVal = 1, int maxVal = 100) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
}

// Функция записи массивов в текстовый файл
bool writeArraysToFile(const string& filename, const int original[], const int sorted[], int size) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << " для записи\n";
        return false;
    }

    // Записываем заголовок и исходный массив
    outFile << "=== СОХРАНЕНИЕ ДАННЫХ МАССИВОВ ===\n\n";
    outFile << "Размер массива: " << size << "\n\n";

    outFile << "ИСХОДНЫЙ МАССИВ:\n";
    for (int i = 0; i < size; i++) {
        outFile << setw(3) << i << ": " << setw(4) << original[i] << "\n";
    }

    outFile << "\nОТСОРТИРОВАННЫЙ МАССИВ:\n";
    for (int i = 0; i < size; i++) {
        outFile << setw(3) << i << ": " << setw(4) << sorted[i] << "\n";
    }

    // Дополнительная статистика
    outFile << "\n=== СТАТИСТИКА ===\n";
    int sumOriginal = 0, sumSorted = 0;
    for (int i = 0; i < size; i++) {
        sumOriginal += original[i];
        sumSorted += sorted[i];
    }

    outFile << "Сумма исходного массива: " << sumOriginal << "\n";
    outFile << "Сумма отсортированного массива: " << sumSorted << "\n";
    outFile << "Минимальный элемент: " << sorted[0] << "\n";
    outFile << "Максимальный элемент: " << sorted[size - 1] << "\n";

    outFile.close();
    return true;
}

// Функция чтения и отображения файла
void displayFileContent(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << " для чтения\n";
        return;
    }

    cout << "\n=== СОДЕРЖИМОЕ ФАЙЛА " << filename << " ===\n";

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

// Функция создания копии массива
void copyArray(const int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

int main() {
    system("chcp 1251");

    cout << "=== СОХРАНЕНИЕ МАССИВОВ В ТЕКСТОВЫЙ ФАЙЛ ===\n\n";

    // Определение размера массива
    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) {
        cerr << "Ошибка: размер массива должен быть положительным!\n";
        return 1;
    }

    // Создание и заполнение массивов
    int* originalArray = new int[size];
    int* sortedArray = new int[size];

    // Заполнение случайными числами
    fillArrayRandom(originalArray, size);

    // Создание копии для сортировки
    copyArray(originalArray, sortedArray, size);

    // Сортировка копии
    selectionSort(sortedArray, size);

    // Вывод массивов на экран
    cout << "\nИсходный массив:\n";
    printArray(originalArray, size);

    cout << "\nОтсортированный массив:\n";
    printArray(sortedArray, size);

    // Запись в файл
    const string filename = "arrays_data.txt";
    if (writeArraysToFile(filename, originalArray, sortedArray, size)) {
        cout << "\nДанные успешно записаны в файл: " << filename << endl;

        // Отображение содержимого файла
        displayFileContent(filename);
    }

    // Дополнительная демонстрация - запись в CSV файл
    const string csvFilename = "arrays_data.csv";
    ofstream csvFile(csvFilename);
    if (csvFile) {
        csvFile << "Index,Original,Sorted\n";
        for (int i = 0; i < size; i++) {
            csvFile << i << "," << originalArray[i] << "," << sortedArray[i] << "\n";
        }
        csvFile.close();
        cout << "\nДанные также записаны в CSV файл: " << csvFilename << endl;
    }

    // Освобождение памяти
    delete[] originalArray;
    delete[] sortedArray;

    // Демонстрация работы с бинарными файлами (как в упражнении 1)
    cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ С БИНАРНЫМИ ФАЙЛАМИ ===\n";

    const int demoSize = 10;
    double demoArray[demoSize];

    // Заполнение демо-массива
    for (int i = 0; i < demoSize; i++) {
        demoArray[i] = (rand() % 100) + 0.5;
    }

    // Запись в бинарный файл
    ofstream binOut("binary_data.bin", ios::binary);
    if (binOut) {
        binOut.write(reinterpret_cast<char*>(demoArray), sizeof(demoArray));
        binOut.close();
        cout << "Демо-массив записан в бинарный файл\n";
    }

    // Чтение из бинарного файла
    double readArray[demoSize];
    ifstream binIn("binary_data.bin", ios::binary);
    if (binIn) {
        binIn.read(reinterpret_cast<char*>(readArray), sizeof(readArray));
        binIn.close();

        cout << "Прочитано из бинарного файла:\n";
        double sum = 0;
        for (int i = 0; i < demoSize; i++) {
            cout << readArray[i] << " ";
            sum += readArray[i];
        }
        cout << "\nСумма: " << sum << endl;
    }

    return 0;
}
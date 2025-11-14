#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Прототипы функций
void printArray(const int arr[], int size);
int calculateSum(const int arr[], int size);
double calculateAverage(const int arr[], int size);
int sumNegative(const int arr[], int size);
int sumPositive(const int arr[], int size);
int sumOddIndex(const int arr[], int size);
int sumEvenIndex(const int arr[], int size);
void findMinMax(const int arr[], int size, int& minVal, int& maxVal, int& minIndex, int& maxIndex);
int productBetweenMinMax(const int arr[], int size);

// Функция вывода массива
void printArray(const int arr[], int size) {
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция расчета суммы элементов
int calculateSum(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Функция расчета среднего значения
double calculateAverage(const int arr[], int size) {
    if (size == 0) return 0.0;
    return static_cast<double>(calculateSum(arr, size)) / size;
}

// Функция суммы отрицательных элементов
int sumNegative(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            sum += arr[i];
        }
    }
    return sum;
}

// Функция суммы положительных элементов
int sumPositive(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            sum += arr[i];
        }
    }
    return sum;
}

// Функция суммы элементов с нечетными индексами
int sumOddIndex(const int arr[], int size) {
    int sum = 0;
    for (int i = 1; i < size; i += 2) {
        sum += arr[i];
    }
    return sum;
}

// Функция суммы элементов с четными индексами
int sumEvenIndex(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i += 2) {
        sum += arr[i];
    }
    return sum;
}

// Функция поиска минимального и максимального элементов
void findMinMax(const int arr[], int size, int& minVal, int& maxVal, int& minIndex, int& maxIndex) {
    if (size == 0) return;

    minVal = maxVal = arr[0];
    minIndex = maxIndex = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            minIndex = i;
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIndex = i;
        }
    }
}

// Функция произведения элементов между min и max
int productBetweenMinMax(const int arr[], int size) {
    int minVal, maxVal, minIndex, maxIndex;
    findMinMax(arr, size, minVal, maxVal, minIndex, maxIndex);

    int start = min(minIndex, maxIndex) + 1;
    int end = max(minIndex, maxIndex);

    if (start >= end) return 0;

    int product = 1;
    for (int i = start; i < end; i++) {
        product *= arr[i];
    }
    return product;
}

// Функция сортировки выбором (как в упражнении 2)
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

int main() {
    system("chcp 1251");

    cout << "=== ОБРАБОТКА МАССИВА (ФУНКЦИИ) ===\n\n";

    const int n = 10;
    int mas[n];

    // Ввод массива
    cout << "Введите " << n << " элементов массива:\n";
    for (int i = 0; i < n; i++) {
        cout << "mas[" << i << "] = ";
        cin >> mas[i];
    }

    cout << "\n";
    printArray(mas, n);

    // Вызовы функций для обработки массива
    cout << "\n--- Результаты обработки ---\n";
    cout << "Сумма всех элементов: " << calculateSum(mas, n) << endl;
    cout << "Среднее значение: " << calculateAverage(mas, n) << endl;
    cout << "Сумма отрицательных: " << sumNegative(mas, n) << endl;
    cout << "Сумма положительных: " << sumPositive(mas, n) << endl;
    cout << "Сумма с нечетными индексами: " << sumOddIndex(mas, n) << endl;
    cout << "Сумма с четными индексами: " << sumEvenIndex(mas, n) << endl;

    int minVal, maxVal, minIndex, maxIndex;
    findMinMax(mas, n, minVal, maxVal, minIndex, maxIndex);
    cout << "Минимальный элемент: " << minVal << " (индекс " << minIndex << ")" << endl;
    cout << "Максимальный элемент: " << maxVal << " (индекс " << maxIndex << ")" << endl;
    cout << "Произведение между min и max: " << productBetweenMinMax(mas, n) << endl;

    // Сортировка
    selectionSort(mas, n);
    cout << "\nОтсортированный массив:\n";
    printArray(mas, n);

    return 0;
}
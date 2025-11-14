#include <iostream>
#include <algorithm>

using namespace std;

// Функция создания массива с максимальными элементами
int* max_vect(int kc, const int a[], const int b[]) {
    int* result = new int[kc]; // Динамическое выделение памяти

    for (int i = 0; i < kc; i++) {
        result[i] = max(a[i], b[i]); // Выбор максимального элемента
    }

    return result; // Возврат указателя на массив
}

// Перегруженная функция для трех массивов
int* max_vect(int kc, const int a[], const int b[], const int c[]) {
    int* result = new int[kc];

    for (int i = 0; i < kc; i++) {
        result[i] = max({ a[i], b[i], c[i] }); // C++11 и выше
    }

    return result;
}

// Функция вывода массива
void printArray(const int arr[], int size, const string& name = "") {
    if (!name.empty()) {
        cout << name << ": ";
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    system("chcp 1251");

    cout << "=== ВОЗВРАТ МАССИВА ИЗ ФУНКЦИИ ===\n\n";

    // Тест 1: Два массива
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 2 };
    int b[] = { 7, 6, 5, 4, 3, 2, 1, 3 };
    int kc = sizeof(a) / sizeof(a[0]);

    cout << "Исходные массивы:\n";
    printArray(a, kc, "Массив A");
    printArray(b, kc, "Массив B");

    int* c = max_vect(kc, a, b);
    cout << "\nРезультирующий массив (max элементов):\n";
    printArray(c, kc, "Массив C");
    delete[] c;

    // Тест 2: Три массива
    int d[] = { 9, 8, 7, 6, 8, 7, 6, 5 };
    cout << "\nДополнительный массив:\n";
    printArray(d, kc, "Массив D");

    int* e = max_vect(kc, a, b, d);
    cout << "\nРезультирующий массив (max из трех):\n";
    printArray(e, kc, "Массив E");
    delete[] e;

    // Тест 3: Динамические массивы
    cout << "\n--- Работа с динамическими массивами ---\n";
    int size;
    cout << "Введите размер массивов: ";
    cin >> size;

    int* arr1 = new int[size];
    int* arr2 = new int[size];

    cout << "Заполните первый массив:\n";
    for (int i = 0; i < size; i++) {
        cout << "arr1[" << i << "] = ";
        cin >> arr1[i];
    }

    cout << "Заполните второй массив:\n";
    for (int i = 0; i < size; i++) {
        cout << "arr2[" << i << "] = ";
        cin >> arr2[i];
    }

    int* result = max_vect(size, arr1, arr2);
    cout << "\nРезультат:\n";
    printArray(result, size);

    // Освобождение памяти
    delete[] arr1;
    delete[] arr2;
    delete[] result;

    return 0;
}
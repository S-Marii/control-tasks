#include <iostream>
#include <vector>

using namespace std;

// Функция поиска с транспозицией
int transpositionSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            // Найден элемент - выполняем транспозицию
            if (i > 0) {
                swap(arr[i], arr[i - 1]);
            }
            return i; // Возвращаем исходную позицию
        }
    }
    return -1; // Элемент не найден
}

// Функция для отображения состояния массива
void displayArray(const int arr[], int size, int foundIndex = -1) {
    cout << "Текущее состояние массива: ";
    for (int i = 0; i < size; i++) {
        if (i == foundIndex) {
            cout << "[" << arr[i] << "] ";
        }
        else {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    system("chcp 1251");

    cout << "=== ПОИСК МЕТОДОМ ТРАНСПОЗИЦИИ ===\n\n";

    const int size = 10;
    int arr[size] = { 5, 2, 8, 1, 9, 3, 7, 4, 6, 0 };

    cout << "Исходный массив:\n";
    displayArray(arr, size);

    // Серия поисков
    int searches[] = { 3, 7, 3, 9, 5, 3 };
    int searchCount = sizeof(searches) / sizeof(searches[0]);

    for (int i = 0; i < searchCount; i++) {
        int key = searches[i];
        cout << "\n--- Поиск элемента " << key << " ---\n";

        int position = transpositionSearch(arr, size, key);

        if (position != -1) {
            cout << "Элемент " << key << " найден на позиции " << position << endl;
            displayArray(arr, size, position);

            // Показываем новую позицию после транспозиции
            int newPosition = (position > 0) ? position - 1 : position;
            cout << "После транспозиции элемент находится на позиции " << newPosition << endl;
        }
        else {
            cout << "Элемент " << key << " не найден!" << endl;
        }
    }

    // Демонстрация эффекта частого доступа
    cout << "\n--- Демонстрация частого доступа ---\n";
    int frequentKey = 3;
    cout << "Многократный поиск элемента " << frequentKey << ":\n";

    for (int i = 0; i < 5; i++) {
        transpositionSearch(arr, size, frequentKey);
        cout << "После поиска #" << (i + 1) << ": ";
        displayArray(arr, size);
    }

    cout << "\nВидно, что часто используемый элемент перемещается к началу массива!\n";

    return 0;
}
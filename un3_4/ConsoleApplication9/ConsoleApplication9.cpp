#include <iostream>

using namespace std;

int recursiveSum(int n) {
    if (n == 1) {
        return 5; 
    }
    return 5 * n + recursiveSum(n - 1);
}

int iterativeSum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += 5 * i;
    }
    return sum;
}

int recursiveSum(int start, int end) {
    if (start > end) {
        return 0;
    }
    if (start == end) {
        return 5 * start;
    }
    return 5 * start + recursiveSum(start + 1, end);
}

int main() {
    system("chcp 1251");

    cout << "=== РЕКУРСИВНОЕ ВЫЧИСЛЕНИЕ СУММЫ РЯДА ===\n\n";

    int n;
    cout << "Введите n (n > 0): ";
    cin >> n;

    if (n <= 0) {
        cout << "Ошибка: n должно быть больше 0!" << endl;
        return 1;
    }

    cout << "\nРяд: ";
    for (int i = 1; i <= n; i++) {
        cout << 5 * i;
        if (i < n) cout << " + ";
    }
    cout << endl;

    int recResult = recursiveSum(n);
    int iterResult = iterativeSum(n);
    int rangeResult = recursiveSum(1, n);

    cout << "Рекурсивный результат: " << recResult << endl;
    cout << "Итерационный результат: " << iterResult << endl;
    cout << "Рекурсивный (диапазон): " << rangeResult << endl;
        
    cout << "\nДемонстрация рекурсии для n = " << n << ":\n";
    for (int i = 1; i <= n; i++) {
        cout << "recursiveSum(" << i << ") = " << recursiveSum(i) << endl;
    }

    return 0;
}
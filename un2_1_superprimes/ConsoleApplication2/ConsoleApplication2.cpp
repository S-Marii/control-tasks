#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

bool isSuperPrime(int n) {
    if (!isPrime(n)) return false;

    int position = 0;
        
    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) {
            position++;
        }
    }
        
    return isPrime(position);
}

int main() {
    system("chcp 1251 > nul");

    cout << "=== Проверка суперпростого числа ===\n\n";

    int number;
    cout << "Введите число для проверки: ";
    cin >> number;

    if (isSuperPrime(number)) {
        cout << "Число " << number << " является суперпростым!\n";
    }
    else {
        cout << "Число " << number << " не является суперпростым.\n";
    }
        
    cout << "\nПервые 10 суперпростых чисел:\n";
    int count = 0;
    for (int i = 2; count < 10; i++) {
        if (isSuperPrime(i)) {
            cout << i << " ";
            count++;
        }
    }
    cout << endl;

    return 0;
}
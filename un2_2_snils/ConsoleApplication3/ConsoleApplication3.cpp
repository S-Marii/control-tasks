#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    system("chcp 1251 > nul");

    cout << "=== Проверка номера СНИЛС ===\n\n";

    string snils;
    cout << "Введите номер СНИЛС (9 цифр + контрольное число): ";
    cin >> snils;
        
    if (snils.length() != 11) {
        cout << "Ошибка: номер должен содержать 11 цифр!\n";
        return 1;
    }
        
    bool validSequence = true;
    for (size_t i = 0; i < 7; i++) {
        if (snils[i] == snils[i + 1] && snils[i] == snils[i + 2]) {
            validSequence = false;
            break;
        }
    }

    if (!validSequence) {
        cout << "Ошибка: в номере не может быть более двух одинаковых цифр подряд!\n";
        return 1;
    }
        
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        int digit = snils[i] - '0';
        sum += digit * (9 - i);
    }

    int calculatedControl;
    if (sum < 100) {
        calculatedControl = sum;
    }
    else if (sum == 100 || sum == 101) {
        calculatedControl = 0;
    }
    else {
        int remainder = sum % 101;
        if (remainder < 100) {
            calculatedControl = remainder;
        }
        else {
            calculatedControl = 0;
        }
    }
        
    int enteredControl = stoi(snils.substr(9, 2));
        
    bool isValid = (calculatedControl == enteredControl);

    cout << "\nРезультаты проверки:\n";
    cout << "Сумма произведений: " << sum << endl;
    cout << "Расчетное контрольное число: " << setw(2) << setfill('0') << calculatedControl << endl;
    cout << "Введенное контрольное число: " << setw(2) << setfill('0') << enteredControl << endl;
    cout << "Номер СНИЛС " << (isValid ? "" : "НЕ ") << "валиден!\n";

    return 0;
}
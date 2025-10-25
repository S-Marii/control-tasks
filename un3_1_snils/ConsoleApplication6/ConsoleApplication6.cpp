#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string cleanSNILS(const string& input) {
    string result;
    for (char c : input) {
        if (isdigit(c)) {
            result += c;
        }
        else if (c != ' ' && c != '-') {
            return ""; // Недопустимый символ
        }
    }
    return result;
}

bool isValidSNILS(const string& snils) {
    string cleaned = cleanSNILS(snils);
        
    if (cleaned.empty() && !snils.empty()) {
        return false;
    }
        
    if (cleaned.length() != 11) {
        return false;
    }
       
    for (size_t i = 0; i < 9; i++) {
        if (i < 7 && cleaned[i] == cleaned[i + 1] && cleaned[i] == cleaned[i + 2]) {
            return false;
        }
    }
        
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        int digit = cleaned[i] - '0';
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
        
    int enteredControl = stoi(cleaned.substr(9, 2));

    return calculatedControl == enteredControl;
}

int main() {
    system("chcp 1251");

    cout << "=== ПРОВЕРКА НОМЕРА СНИЛС ===\n\n";

    string snils;
    cout << "Введите номер СНИЛС: ";
    getline(cin, snils);

    bool isValid = isValidSNILS(snils);

    cout << "\nРезультат проверки: " << (isValid ? "VALID" : "INVALID") << endl;
       
    cout << "\nТестовые примеры:\n";
    cout << "123-456-789 01: " << (isValidSNILS("123-456-789 01") ? "VALID" : "INVALID") << endl;
    cout << "12345678901: " << (isValidSNILS("12345678901") ? "VALID" : "INVALID") << endl;
    cout << "11223344595: " << (isValidSNILS("11223344595") ? "VALID" : "INVALID") << endl;

    return 0;
}
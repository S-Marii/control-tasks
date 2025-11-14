#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Функция записи стихотворения в файл
bool writePoemToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << " для записи\n";
        return false;
    }

    cout << "=== ЗАПИСЬ СТИХОТВОРЕНИЯ В ФАЙЛ ===\n\n";
    cout << "Введите стихотворение (для завершения введите пустую строку):\n";

    string line;
    int lineCount = 0;

    // Чтение строк с клавиатуры
    while (true) {
        cout << "Строка " << (lineCount + 1) << ": ";
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        outFile << line << endl;
        lineCount++;
    }

    outFile.close();

    if (lineCount > 0) {
        cout << "\nСтихотворение успешно записано в файл '" << filename << "'\n";
        cout << "Количество строк: " << lineCount << endl;
        return true;
    }
    else {
        cout << "Не было введено ни одной строки.\n";
        return false;
    }
}

// Функция чтения и вывода содержимого файла
void readAndDisplayFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << " для чтения\n";
        return;
    }

    cout << "\n=== СОДЕРЖИМОЕ ФАЙЛА ===\n";

    string line;
    int lineNumber = 1;

    while (getline(inFile, line)) {
        cout << lineNumber << ": " << line << endl;
        lineNumber++;
    }

    inFile.close();
}

// Функция добавления текста в существующий файл
bool appendToFile(const string& filename) {
    ofstream outFile(filename, ios::app);
    if (!outFile) {
        cerr << "Ошибка: невозможно открыть файл " << filename << " для добавления\n";
        return false;
    }

    cout << "\n=== ДОБАВЛЕНИЕ ТЕКСТА В ФАЙЛ ===\n";
    cout << "Введите дополнительные строки (пустая строка для завершения):\n";

    string line;
    int addedLines = 0;

    while (true) {
        cout << "Доп. строка: ";
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        outFile << line << endl;
        addedLines++;
    }

    outFile.close();

    if (addedLines > 0) {
        cout << "Добавлено строк: " << addedLines << endl;
    }

    return addedLines > 0;
}

int main() {
    system("chcp 1251");

    const string filename = "poem.txt";

    // Основная запись стихотворения
    if (writePoemToFile(filename)) {
        // Чтение и вывод содержимого
        readAndDisplayFile(filename);

        // Предложение добавить текст
        char choice;
        cout << "\nХотите добавить еще текст? (y/n): ";
        cin >> choice;
        cin.ignore(); // Очистка буфера

        if (choice == 'y' || choice == 'Y') {
            if (appendToFile(filename)) {
                readAndDisplayFile(filename);
            }
        }
    }

    // Демонстрация работы с разными файлами
    cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ВОЗМОЖНОСТИ ===\n";

    // Запись в другой файл
    const string anotherFile = "another_poem.txt";
    cout << "\nСоздаем еще один файл...\n";
    if (writePoemToFile(anotherFile)) {
        readAndDisplayFile(anotherFile);
    }

    return 0;
}
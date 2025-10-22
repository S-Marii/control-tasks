#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

class Target {
private:
    double centerX, centerY;
        
    const double radius1 = 2.0;
    const double radius2 = 4.0;
    const double radius3 = 6.0;

public:
    Target() : centerX(0.0), centerY(0.0) {}
        
    void setRandomCenter() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(-3.0, 3.0);
        centerX = dis(gen);
        centerY = dis(gen);
    }
        
    int calculateScore(double x, double y, bool useInterference = false) {
        double shotX = x;
        double shotY = y;
                
        if (useInterference) {
            random_device rd;
            mt19937 gen(rd());
            normal_distribution<> dis(0.0, 0.5);
            shotX += dis(gen);
            shotY += dis(gen);
        }

        double distance = sqrt(pow(shotX - centerX, 2) + pow(shotY - centerY, 2));

        if (distance <= radius1) return 10;
        if (distance <= radius2) return 5;
        if (distance <= radius3) return 1;
        return 0;
    }

    void printCenter() const {
        cout << "Центр мишени: (" << fixed << setprecision(1)
            << centerX << ", " << centerY << ")\n";
    }
};

int main() {
    system("chcp 1251");

    cout << "=== СТРЕЛЬБА ПО МИШЕНИ ===\n\n";

    Target target;
    char choice;
        
    cout << "Выберите режим стрельбы:\n";
    cout << "N - нормальный (центр в 0,0)\n";
    cout << "R - случайный центр\n";
    cout << "I - с помехами\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    bool useRandomCenter = false;
    bool useInterference = false;

    switch (choice) {
    case 'R':
    case 'r':
        useRandomCenter = true;
        target.setRandomCenter();
        break;
    case 'I':
    case 'i':
        useInterference = true;
        break;
    default:
        useRandomCenter = false;
        useInterference = false;
    }

    if (useRandomCenter) {
        target.printCenter();
    }

    const int TARGET_SCORE = 50;
    int totalScore = 0;
    int shotsCount = 0;

    cout << "\nЦель: набрать " << TARGET_SCORE << " очков!\n";
        
    while (totalScore < TARGET_SCORE) {
        double x, y;
        cout << "\nВыстрел #" << (shotsCount + 1) << "\n";
        cout << "Введите координаты x y: ";
        cin >> x >> y;

        int score = target.calculateScore(x, y, useInterference);
        totalScore += score;
        shotsCount++;

        cout << "Результат: " << score << " очков\n";
        cout << "Всего: " << totalScore << "/" << TARGET_SCORE << " очков\n";
    }
        
    string level;
    if (shotsCount <= 7) level = "СНАЙПЕР";
    else if (shotsCount <= 15) level = "СТРЕЛОК";
    else level = "НОВИЧОК";

    cout << "\n================================\n";
    cout << "ВЫ УСПЕШНО ЗАВЕРШИЛИ СТРЕЛЬБУ!\n";
    cout << "================================\n";
    cout << "Количество выстрелов: " << shotsCount << "\n";
    cout << "Итоговый счет: " << totalScore << "\n";
    cout << "Ваш уровень: " << level << "\n";

    return 0;
}
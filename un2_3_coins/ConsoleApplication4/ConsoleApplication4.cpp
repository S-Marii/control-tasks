#include <iostream>
#include <vector>

using namespace std;

int main() {
    system("chcp 1251 > nul");

    cout << "=== Размен монет ===\n\n";
        
    vector<int> coins = { 10, 5, 2, 1 };
    int amount;

    cout << "Введите сумму для размена: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Ошибка: сумма должна быть положительной!\n";
        return 1;
    }

    cout << "\nРазмен суммы " << amount << " рублей:\n";
    cout << "========================\n";

    int remaining = amount;
    int totalCoins = 0;
        
    for (int coin : coins) {
        if (remaining >= coin) {
            int count = remaining / coin;
            cout << "Монета " << coin << " руб.: " << count << " шт.\n";
            totalCoins += count;
            remaining %= coin;
        }
    }

    cout << "\nВсего монет: " << totalCoins << endl;

    return 0;
}
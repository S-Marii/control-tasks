#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int Myroot(double a, double b, double c, double& x1, double& x2);

int Myroot(double a, double b, double c, double& x1, double& x2) {
    
    if (a == 0) {
        if (b == 0) {
            return -1;
        }
        x1 = x2 = -c / b;
        return 0;
    }
        
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1;
    }
    else if (discriminant == 0) {
        x1 = x2 = -b / (2 * a);
        return 0;
    }
    else {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        return 1;
    }
}

int Myroot(double a, double b, double c, double* x1, double* x2) {
    if (x1 == nullptr || x2 == nullptr) {
        return -1;
    }

    double temp_x1, temp_x2;
    int result = Myroot(a, b, c, temp_x1, temp_x2);

    *x1 = temp_x1;
    *x2 = temp_x2;

    return result;
}

void printRoots(int result, double x1, double x2) {
    cout << fixed << setprecision(4);

    switch (result) {
    case -1:
        cout << "Корней уравнения нет" << endl;
        break;
    case 0:
        cout << "Корень уравнения один x1 = x2 = " << x1 << endl;
        break;
    case 1:
        cout << "Корни уравнения x1 = " << x1 << ", x2 = " << x2 << endl;
        break;
    default:
        cout << "Неизвестный результат" << endl;
    }
}

int main() {
    system("chcp 1251");

    cout << "=== ВЫЧИСЛЕНИЕ КОРНЕЙ КВАДРАТНОГО УРАВНЕНИЯ ===\n\n";

    double a, b, c;
    cout << "Введите коэффициенты квадратного уравнения (a b c): ";
    cin >> a >> b >> c;

    double x1, x2;
        
    int result = Myroot(a, b, c, x1, x2);

    cout << "\nРезультат (ссылки):\n";
    printRoots(result, x1, x2);
        
    double x1_ptr, x2_ptr;
    int result_ptr = Myroot(a, b, c, &x1_ptr, &x2_ptr);

    cout << "\nРезультат (указатели):\n";
    printRoots(result_ptr, x1_ptr, x2_ptr);
        
    cout << "\n--- Тестовые примеры ---\n";

    struct TestCase {
        double a, b, c;
        string description;
    };

    TestCase tests[] = {
        {1, -5, 6, "x² - 5x + 6 = 0 (два корня)"},
        {1, -4, 4, "x² - 4x + 4 = 0 (один корень)"},
        {1, 1, 1, "x² + x + 1 = 0 (нет корней)"},
        {0, 2, -4, "2x - 4 = 0 (линейное)"},
        {0, 0, 5, "5 = 0 (нет решений)"}
    };

    for (const auto& test : tests) {
        cout << "\n" << test.description << ":\n";
        double test_x1, test_x2;
        int test_result = Myroot(test.a, test.b, test.c, test_x1, test_x2);
        printRoots(test_result, test_x1, test_x2);
    }

    return 0;
}
#include <iostream>
#include <cmath>
int main () {
    double x, y, C, K;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение y: ";
    std::cin >> y;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    if (std::cin.fail()) {
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    if (C == 0) {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    if (K == 0) {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    double A = x + y;
    double D = std::fabs(C - A);
    double S = 10.1 + (A / C) + (D / std::pow(K,2));
    std::cout << "\nРезультаты вычислений: " << std::endl;
    std::cout << "A = x + y = " << x << " + " << y << " = " << A << std::endl;
    std::cout << "D = |C - A| = |" << C << " - " << A << "| = " << D << std::endl;
    std::cout << "S = 10.1 + A/C + D/K^2 = " << S << std::endl;
    std::cout << " = 10.1 + " << A << " / " << C << " + " << D << "/(" << "^2)" << std::endl;
    return 0;
}
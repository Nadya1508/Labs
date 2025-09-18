#include <iostream>
#include <cmath>
int main () {
    double x, p, h, K, C, D;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение p: ";
    std::cin >> p;
    std::cout << "Введите значение h: ";
    std::cin >> h;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    if(std::cin.fail()) {
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    if(K == 0 || C == 0 || D == 0) {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    if(h <= 0) {
        std::cout <<"Ошибка: невозможно вычислить натуральный логарифм из неположительного числа" << std::endl;
        return 1;
    }
    double A = x - p;
    double B = std::log(h);
    double denominator = K * C * D;
    double Y = 0.78 * B + std::pow(A,3) / denominator;
    std::cout << "\nРезультаты вычислений: " << std::endl;
    std::cout << "A = x - p = " << x << " - " << p << " = " << A << std::endl;
    std::cout << "B = ln(h) = ln( " << h << ") = " << B << std::endl;
    std::cout << "Y = 0.78*B + A^3/(K*C*D) = " << Y << std::endl;
    std::cout << " = 0.78*" << B << " + " << std::pow(A,3) << " / (" << K << " * " << C << " * " << D << ")" << std::endl;
    std::cout << " = " << (0.78 * B) << " + " << (std::pow(A,3) / (K * C * D)) << std::endl;
    return 0;
}
#include <iostream>
#include <cmath>
int main(){
    double x, p, K, D, C;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение p: ";
    std::cin >> p;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    if (std::cin.fail()){
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    double A = x + std::sin(p);
    double B = std::exp(K);
    if (A == 0 || B == 0 ) {
        std:: cout << "Ошибка: деление на ноль!" << std::endl;
        return 1;
    }
    double Y = 1 + std::pow(K,2) / (2 * A * B) - B + (D * C);
    std::cout << " \nРезультаты вычислений: " << std::endl;
    std::cout << "A = x + sin(p) = " << x << " + sin(" << p << ") = " << A << std::endl;
    std::cout << "B = e^K = e^" << K << " = " << B << std::endl;
    std::cout << "Y = 1 + K^2/(2*A*B) - B + D*C = " << Y << std::endl;
    std::cout << "  = 1 + " << std::pow(K, 2) << "/(" << 2 * A * B << ") - " << B << " + " << D * C << std::endl;
    std::cout << "  = 1 + " << (std::pow(K, 2) / (2 * A * B)) << " - " << B << " + " << D * C << std::endl;
    return 0;

}
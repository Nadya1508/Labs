#include <iostream>
#include <cmath>
int main () {
    double n, m, x, K;
    std::cout << "Введите значение n: ";
    std::cin >> n;
    std::cout << "Введите значение m: ";
    std::cin >> m;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    if(std::cin.fail()){
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    double A = std::fabs(n + m);
    if (A == 0) {
        std::cout <<"Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    if (std::cos(x) == 0) {
        std::cout << "Ошибка: тангенс не определён" << std::endl;
        return 1;
    }
    double D = std::tan(x);
    double y = 1.29 + (K / A) + std::pow(D,2);
    std::cout << "\nРезультаты вычислений: " <<std::endl;
    std::cout << "A = |n + m| = |" << n << " + " << m << "| = " << A << std::endl;
    std::cout << "D = tg(x) = tg(" << x << ") = " << D << std::endl;
    std::cout << "y = 1.29 + K/A + D^2 = " << y << std::endl;
    std::cout << "  = 1.29 + " << K << "/" << A << " + " << std::pow(D, 2) << std::endl;
    std::cout << "  = 1.29 + " << (K / A) << " + " << std::pow(D, 2) << std::endl;
    return 0;
}
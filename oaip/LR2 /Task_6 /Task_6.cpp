#include <iostream>
#include <cmath>
int main () {
    double x, d, C, K;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение d: ";
    std::cin >> d;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    if(std::cin.fail()) {
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    if (K == 0) {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    if (x <= 0) {
        std::cout << "Ошибка: невозможно вычислить десятичный логарифм из неположительного числа" << std::endl;
        return 1;
    }
    double A = std::log10(x);
    double B = x + std::exp(d);
    double Y = (A + B) - (std::pow(C,2) / K);
    std::cout << "\nРезультаты вычислений: " << std::endl;
    std::cout << "A = lg(x) = lg(" << x << ") = " << A << std::endl;
    std::cout << "B = x + e^d = " << x << "+ e^" << d << " = " << B << std::endl;
    std::cout << "Y = (A + B) - (C^2 / K) = " << Y << std::endl;
    std::cout << " = ( " << A << " + " << B << ") - (" << std::pow(C,2) << " / " << K << ")" << std::endl;
    std::cout << " = " << (A + B) << " - " << (std::pow(C,2) / K) << std::endl;
return 0;
}
    
      
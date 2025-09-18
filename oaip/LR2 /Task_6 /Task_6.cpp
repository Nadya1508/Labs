#include <iostream> 
#include <cmath>
int main () {
    double x, p, n, K, D;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение p: ";
    std::cin >> p;
    std::cout << "Введите значение n: ";
    std::cin >> n;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    if (std::cin.fail()) {
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    if (K == 0 || D == 0) {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    double B = cos(x);
    double C = p - n;
    double Q = (pow(B,2) / (K * D)) + (B * pow(C,3));
    std::cout << " \nРезультаты вычислений: " << std::endl;
    std::cout << "B = cos(x) = cos(" << x << ") = " << B << std::endl;
    std::cout << "C = p - n = " << p << " - " << n << " = " << C << std::endl;
    std::cout << "Q = B^2/(K*D) + B*C^3 = " << Q << std::endl;
    std::cout << " = " << pow(B,2) << "/(" << K*D << ") + " << B << "*" << (B * pow (C,3)) << std::endl;
    return 0;
}
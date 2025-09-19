#include <iostream>
#include <cmath>
int main () {
    double x, k, z, C, D;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение k: ";
    std::cin >> k;
    std::cout << "Введите значение z: ";
    std::cin >> z;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    if(x <= 0) {
        std::cout << "Ошибка: логарифм определён только для x > 0!" << std::endl;
        return 1;
    }
    if (z < 0) {
        std::cout << "Ошибка: корень из отрицательного числа!" << std::endl;
        return 1;
    }
    double A = std::log(x) - k;
    double B = std::sqrt(z);
    if (0.75 * A == 0) {
        std::cout << "Ошибка: деление на ноль!" << std::endl;
        return 1;
    }
    double Y = std::pow(D,2) + (std::pow(C,2) / (0.75 * A)) + B;
    std::cout << "Результат Y = " << Y << std::endl;
    return 0;
}
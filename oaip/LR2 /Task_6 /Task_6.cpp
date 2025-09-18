#include <iostream>
#include <cmath>
int main () {
    double x, y, z, K, C, D;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение y: ";
    std::cin >> y;
    std::cout << "Введите значение z: ";
    std::cin >> z;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    if (std::cin.fail()) {
        std::cout << "Ошибка ввода! Пожалуйста, введите числовые значения." << std::endl;
        return 1;
    }
    if (z < 0) {
        std::cout <<"Ошибка! Невозможно вычислить квадратный корень из отрицательного числа" << std::endl;
        return 1;
    }
    if (K - C * D == 0) {
        std::cout << "Ошибка: деление на ноль" << std:: endl;
        return 1;
    }
    double A = x - y;
    double B = std::sqrt(z);
    double T = std::cos(x) + (std::pow(A,2) / (K - C * D)) - B;
    std::cout << "\nРезультаты вычислений: " << std::endl;
    std::cout << "A = x - y = " << x << " - " << y << " = " << A << std::endl;
    std::cout << "B = √z = √" << z << " = " << B << std::endl;
    std::cout << "T = cos(x) + A^2/(K -C * D) - B = " << T << std::endl;
    std::cout << " = cos( " << x << ") + " << std::pow(A,2) << "/(" << K << " - " << C * D << ") - " << B << std::endl;
    return 0;
}
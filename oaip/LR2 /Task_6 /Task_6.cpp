#include <iostream>
#include <cmath>
int main() {
    double x, z, p, K, C, D;
    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение z: ";
    std::cin >> z;
    std::cout << "Введите значение p: ";
    std::cin >> p;
    std::cout << "Введите значение K: ";
    std::cin >> K;
    std::cout << "Введите значение C: ";
    std::cin >> C;
    std::cout << "Введите значение D: ";
    std::cin >> D;
    if (C * D == 0) {
        std::cout << "Ошибка: деление на ноль" << std::endl;
        return 1;
    }
    double A = std::sin(x) -z;
    double B = std::fabs(p-x);
    double Y = std::pow(A + B, 2) - (K / (C * D));
    std::cout << "\nРезультаты вычислений: " << std::endl;
    std::cout << "A = sin (" << x << ") - " << z << " = " << A << std::endl;
    std::cout << " B = | " << p << " - " << x << " | = " << B << std::endl;
    std::cout << "C * D = " << C << " * " << D << " = " << C * D << std::endl;
    std::cout << "Y = (" << A << " + " << B << ")^2 - " << K << " / (" << C << " * " << D << " ) = " <<  Y << std::endl;
    return 0;
}
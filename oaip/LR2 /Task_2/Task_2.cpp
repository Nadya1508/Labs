#include <iostream> 
int main() {
    double x, y, z;
    std::cout << "Введите три положительных числа (x, y, z): ";
    std::cin >> x >> y >> z;
    if (x <= 0 || y <= 0 || z <= 0) {
        std::cout << "Ошибка: все числа должны быть положительными!!!";
        return 1;
    }
    
    
}
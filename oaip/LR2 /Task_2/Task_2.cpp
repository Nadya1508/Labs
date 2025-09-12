#include <iostream> 
int main() {
    double x, y, z;
    std::cout << "Введите три положительных числа (x, y, z): ";
    std::cin >> x >> y >> z;
    if (x <= 0 || y <= 0 || z <= 0) {
        std::cout << "Ошибка: все числа должны быть положительными!!!";
        return 1;
    }
    bool is_triangle = true;

    if (y +z <= x) {
        is_triangle = false;
    } else if (x +z <= y) {
        is_triangle = false;
    } else if (x + y <= z){
        is_triangle = false;
    }
    if (is_triangle) {
        std::cout << "Треугольник со сторонами " << x << " , " << y << " , " << z << "существует." << std::endl;
    } else if (is_triangle) {
        std::cout << "Треугольник со сторонами " << x << " , " << y << " , " << z << "НЕ существует." << std::endl;
    }
     
    return 0;
}
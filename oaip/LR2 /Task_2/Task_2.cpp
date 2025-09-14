#include <iostream> ё
using namespace std;
int main() {
    double x, y, z;
    cout << "Введите три положительных числа (x, y, z): ";
    cin >> x >> y >> z;
    if (x <= 0 || y <= 0 || z <= 0) {
        cout << "Ошибка: все числа должны быть положительными!!!" << endl;
        return 1;
    }
    bool exists = true;

    if (y +z <= x) {
        is_triangle = false;
    } else if (x +z <= y) {
        is_triangle = false;
    } else if (x + y <= z){
        is_triangle = false;
    }
    if (is_triangle) {
        cout << " Треугольник со сторонами " << x << " , " << y << " , " << z <<  " существует. " << std::endl;
    } else if (is_triangle) {
        cout << " Треугольник со сторонами " << x << " , " << y << " , " << z <<  " НЕ существует. " << std::endl;
    }
     
    return 0;
}
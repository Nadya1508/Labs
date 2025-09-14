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
        exists = false;
    } else if (x +z <= y) {
       exists = false;
    } else if (x + y <= z){
      exists = false;
    }
    cout << "/n===Результат проверки=== " << endl;
    cout << "Сторона x = " << x << endl;
    cout << "Сторона y = " << y << endl;
    cout << "Сторона z = " << z << endl;
    if (exists) {
        cout << " Треугольник существует  " << endl;
    } else if (exists) {
        cout << " Треугольник НЕ существует " << endl;
    }
     
    return 0;
}
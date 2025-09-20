#include <iostream>
using namespace std;

double square(double x) {
    return x * x;
}
double sqrt_newton(double x) {
    if (x <= 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; ++i)
    guess = 0.5 * (guess + x / guess);
    return guess;
}
double distance(double x1, double y1, double x2, double y2) {
    return sqrt_newton(square(x2 - x1) + square(y2 - y1));
}
int main () {
    double x1, y1, r, x2, y2, R;
    cout << "Введите координаты центра первого круга  M1(x1 y1): ";
    cin >> x1 >> y1;
    cout << "Введите радиус первого круга r: ";
    cin >> r;
    cout << "Введите координаты центра второго круга M2(x2 y2): ";
    cin >> x2 >> y2;
    cout << "Введите радиус второго круга R: ";
    cin >> R;
    double d = distance(x1, y1, x2, y2);
    cout << "Расстояние между центрами: " << d << endl;          
    if (d + r <= R) {
        cout << "Да" << endl;
    }
    else if (d +R <= r) {
        cout << "Да, но справедливо обратное для двух фигур" << endl;
    }
    else if (d < r + R) {
        cout << "Фигуры пересекаются" << endl;
    }
    else {
        cout << "Ни одно условие не выполнено" << endl;
    }
    return 0;
}

#include <iostream>
using namespace std;

double evaluate(double a, double b, double c, double x) {
    return a * x * x * x * x + b * x * x * x + c * x * x + b * x + a;
}
void solveEquation(double a, double b, double c) {
    cout << "Решение уравнения: " << a << "x^4 + " << b << "x^3 + " << c << "x^2 + " << b << "x + " << a << " = 0\n";
    const double step = 0.01;
    const double epsilon = 0.0001;
    const int range = 100;

    bool found = false;

    for (int i = -range * 100; i <= range * 100; ++i) {
      double x = i * step;  
      double fx = evaluate(a, b, c, x);
      if (fx * fx < epsilon * epsilon) {
        cout << "x ≈ " << x << "\n";
        found = true;
      }
    }
    if (!found) {
        cout << "Действительных корней не найдено\n";
    }
}
int main() {
    double a, b, c;
    cout << "Введите коэффициенты a, b, c: ";
    cin >> a >> b >> c;

    solveEquation(a, b, c);
    return 0;
}
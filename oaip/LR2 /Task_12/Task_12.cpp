#include <iostream>
using namespace std;

double evaluate(double p, double q, double x){
return x * x * x + p * x + q;
}
void solveCubic(double p, double q){
    cout << "Решение уравнения: x^3 + " << p << " x + " << q << " = 0\n";

    const double step = 0.001;
    const double epsilon = 0.0001;
    const int range = 1000;

    bool found = false;

    for (int i = -range; i <= range; ++i) {
        double x = i * step;
        double fx = evaluate (p, q, x);
        if (fx * fx < epsilon * epsilon){
            cout << " x ≈ " << x << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Действительных корней не найдено\n";
    }
}
int main() {
    double p, q;
    cout << "Введите коэффициенты p и q: ";
    cin >> p >> q;

    solveCubic(p,q);
    return 0;
}
#include <iostream>
using namespace std;

double sqrt_newton(double x) {
    if (x <= 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; ++i) {
        if (guess == 0) return 0;
        guess = 0.5 * (guess + x / guess);
    }
    return guess;
}

int solveQuadratic(double a, double b, double c, double roots[2]) {
    if (a == 0) {
        if (b == 0) return 0;
        roots[0] = -c / b;
        return 1;
    }

    double D = b * b - 4 * a * c;
    if (D < 0) return 0;

    double sqrtD = sqrt_newton(D);
    if (D == 0) {
        roots[0] = -b / (2 * a);
        return 1;
    } else {
        roots[0] = (-b - sqrtD) / (2 * a);
        roots[1] = (-b + sqrtD) / (2 * a);
        return 2;
    }
}

void solveBiquadratic(double a, double b, double c) {
    cout << "Решение уравнения: " << a << "x^4 + " << b << "x^2 + " << c << " = 0\n";

    if (a == 0 && b == 0) {
        if (c == 0) {
            cout << "x — любое число\n";
        } else {
            cout << "Нет действительных корней\n";
        }
        return;
    }
    if(a == 0) {
        double xSquared = -c / b;
        if (xSquared > 0) {
            double x1 = sqrt_newton(xSquared);
            double x2 = -x1;
            cout << "x = " << x1 << ", = " << x2 << "\n";
        } else if (xSquared == 0) {
            cout << "x = 0\n";
        } else {
            cout << "Нет действительных корней\n";
        }
        return;
    }
    double yRoots[2];
    int numYRoots;
    
    bool hasRealRoots = false;
    for (int i = 0; i < numYRoots; ++i) {
        if (yRoots[i] > 0) {
            double x1 = sqrt_newton(yRoots[i]);
            double x2 = -x1;
            cout << "x = " << x1 << ", x = " << x2 << "\n";
            hasRealRoots = true;
        } else if (yRoots[i] == 0) {
            cout << "x = 0\n";
            hasRealRoots = true;
        }
    }

    if (!hasRealRoots) {
        cout << "Нет действительных корней\n";
    }
}

int main() {
    double a, b, c;
    cout << "Введите коэффициенты a, b, c: ";
    cin >> a >> b >> c;

    solveBiquadratic(a, b, c);
    return 0;
}

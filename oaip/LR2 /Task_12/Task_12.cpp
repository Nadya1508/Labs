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
int solveQuadratic(double a, double b, double c, double roots [2]) {
    if ( a == 0) {
        if (b == 0){
            return 0;
        }
        roots [0] = -c / b;
        return 1;
    }
    double D = b * b - 4 * a * c;
    if (D < 0) {
        return 0;
    }
    double sqrtD = sqrt_newton(D);
    if (D == 0) {
        roots[0] = -b / (2 * a);
        return 1;
    } else {
        roots[0] = (-b - sqrtD) / (2 * a);
        roots[1] = (-b + sqrtD) / (2 *a);
        return 2;
    }
}
void solveBiquadratic(double a, double b, double c) {
    cout << "Решение уравнения " << a << "x^4 + " << b << "x^2 + " << c << " = 0:" << endl;
    if (a == 0 && b == 0) {
        if (c == 0) {
            cout << "x - любое число" << endl;
        } else {
            cout << "Действительных корней нет" << endl;
        }
        return;
    }
    if (a == 0) {
        double roots[2];
        int numRoots = solveQuadratic(b, 0, c, roots);

        if(numRoots == 0){
            cout << "Действительныыз корней нет" << endl;
        } else {
            bool hasRealRoots = false;   
            for (int i = 0; i < numRoots; i++) {
             if(roots[i] > 0){
                double x1 = sqrt_newton(roots[i]);
                double x2 = -sqrt_newton(roots[i]);
                cout << "x = " << x1 << ", x = " << x2;
                if (i < numRoots -1 ) cout << " , ";
                hasRealRoots = true;
             } else if (roots[i] == 0) {
                cout << "x = 0";
                if (i < numRoots - 1) cout << " , ";
                hasRealRoots = true;
             }
            }
            if (!hasRealRoots) {
            cout << "Действительных корней нет";
        } 
        cout << endl;
        }
        return;
    }
    double yRoots[2];
    int numYRoots = solveQuadratic(a, b, c, yRoots);

    if (numYRoots == 0) {
        cout << "Действительных корней нет" << endl;
        return;
    }
    bool hasRealRoots = false;
    bool first = true;

    for (int i = 0; i < numYRoots; i++) {
        if(yRoots[i] > 0) {
            double x1 = sqrt_newton(yRoots[i]);
            double x2 = -sqrt_newton(yRoots[i]);
            if (!first) cout << " , ";
            cout << "x = " << x1 << " , x = " << x2;
            hasRealRoots = true;
            first = false;
        } else if (yRoots == 0) {
            if (!first) cout << " , ";
            cout << "x = 0";
            hasRealRoots = true;
            first = false;
        }
    }
    if (!hasRealRoots){
        cout << "Действительных корней нет";
    }
    cout << endl;
}
int main() {
    cout << "Решение биквадратного уравнения ax^4 + bx^2 + c = 0" << endl;
    double a, b, c;
    cout << "Введите коэффициент a: ";
    cin >> a;
    cout << "Введите коэффициент b: ";
    cin >> b;
    cout << "Введите коэффициент c: ";
    cin >> c;

    solveBiquadratic(a, b, c);

    return 0;
}

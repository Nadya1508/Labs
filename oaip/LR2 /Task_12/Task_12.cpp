#include <iostream>
using namespace std;

double my_abs(double x) {
    return x < 0 ? -x : x;
}

double cubeRoot(double x) {
    if (x == 0.0) return 0.0;
    
    double guess = x;
    double precision = 1e-10;
    
    for (int i = 0; i < 50; i++) {
        double newGuess = (2.0 * guess + x / (guess * guess)) / 3.0;
        if (my_abs(newGuess - guess) < precision) {
            return newGuess;
        }
        guess = newGuess;
    }
    return guess;
}

void solveCubic(double p, double q) {
    cout << "Решение уравнения: x^3 + " << p << "x + " << q << " = 0\n";
    
    if (p == 0 && q == 0) {
        cout << "Три одинаковых корня:\n";
        cout << "x1 = x2 = x3 = 0\n";
        return;
    }
    
    double discriminant = (q * q) / 4.0 + (p * p * p) / 27.0;
    
    if (discriminant > 1e-10) {
       
        double sqrtD = sqrt(discriminant);
        double u = cubeRoot(-q/2.0 + sqrtD);
        double v = cubeRoot(-q/2.0 - sqrtD);
        double realRoot = u + v;
        
        cout << "Один вещественный корень:\n";
        cout << "x1 = " << realRoot << "\n";
    }
    else if (my_abs(discriminant) < 1e-10) {
        
        double root1 = 3.0 * q / p;
        double root2 = -3.0 * q / (2.0 * p);
        
        cout << "Два вещественных корня:\n";
        cout << "x1 = " << root1 << "\n";
        cout << "x2 = x3 = " << root2 << "\n";
    }
    else {
       
        cout << "Три различных вещественных корня (найдены численным методом):\n";
        
        const double step = 0.001;
        const double range = 10.0;
        int rootsFound = 0;
        double lastRoot = -range - 1;
        
        for (double x = -range; x <= range && rootsFound < 3; x += step) {
            double fx = x*x*x + p*x + q;
            
            if (fx > -0.001 && fx < 0.001) {
                double diff = x - lastRoot;
                if (diff > 0.01 || diff < -0.01) {
                    cout << "x" << ++rootsFound << " = " << x << "\n";
                    lastRoot = x;
                }
            }
        }
        
        if (rootsFound == 0) {
            cout << "Корни не найдены в диапазоне [-10, 10]\n";
        }
    }
}

int main() {
    double p, q;
    
    cout << "Решение уравнения x^3 + px + q = 0\n";
    cout << "Введите коэффициент p: ";
    cin >> p;
    cout << "Введите коэффициент q: ";
    cin >> q;
    
    solveCubic(p, q);
    
    return 0;
}
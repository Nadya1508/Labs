#include <iostream>
using namespace std;

int sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

double cubeRoot(double x) {
    if (x == 0.0) return 0.0;
    
    double guess = x;
    double precision = 1e-10; 
    double difference;
    
    do {
        double guessCubed = guess * guess * guess;
        double newGuess = guess - (guessCubed - x) / (3.0 * guess * guess);
        difference = newGuess - guess;
        guess = newGuess;
    } while (difference > precision || difference < -precision);
    
    return guess;
}

void solveCubic(double p, double q) {
    cout << "Решение уравнения: x^3 + " << p << "x + " << q << " = 0\n";
    
    double discriminant = (q * q) / 4.0 + (p * p * p) / 27.0;
    
    if (discriminant > 0) {
        double sqrtD = cubeRoot(-q/2.0 + cubeRoot(discriminant));
        double sqrtD2 = cubeRoot(-q/2.0 - cubeRoot(discriminant));
        double realRoot = sqrtD + sqrtD2;
        
        cout << "Один вещественный корень:\n";
        cout << "x1 = " << realRoot << "\n";
        cout << "x2 = " << -realRoot/2.0 << " + i*" << (cubeRoot(3.0)*fabs(realRoot)/2.0) << "\n";
        cout << "x3 = " << -realRoot/2.0 << " - i*" << (cubeRoot(3.0)*fabs(realRoot)/2.0) << "\n";
    }
    else if (discriminant == 0) {
        double root1 = 3.0 * q / p;
        double root2 = -3.0 * q / (2.0 * p);
        
        cout << "Три вещественных корня (два совпадают):\n";
        cout << "x1 = " << root1 << "\n";
        cout << "x2 = x3 = " << root2 << "\n";
    }
    else {
        double r = cubeRoot(sqrt(-(p*p*p)/27.0));
        double phi = acos(-q/(2.0*r));
        
        cout << "Три различных вещественных корня:\n";
        cout << "x1 = " << 2.0*r*cos(phi/3.0) << "\n";
        cout << "x2 = " << 2.0*r*cos((phi + 2.0*M_PI)/3.0) << "\n";
        cout << "x3 = " << 2.0*r*cos((phi + 4.0*M_PI)/3.0) << "\n";
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
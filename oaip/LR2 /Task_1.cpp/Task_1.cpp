#include <iostream>
using namespace std;
int main() { 
    double x;
    cout << "Enter x: ";
    cin >> x;
    double x2 = x * x;
    double x3 = x2 * x; 
    double part1 = 23 * x3 +32 * x;
    double part2 = 69 * x2 + 8;
    double A = part1 + part2;
    double B = -part1 + part2;
    
    cout << "23x^3 + 69x^2 + 32x + 8 = " << A << endl;
    cout << "-23x^3 + 69x^2 - 32x + 8 = " << B << endl;
    
    return 0;
}
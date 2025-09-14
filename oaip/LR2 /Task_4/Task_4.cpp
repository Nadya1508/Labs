#include <iostream>
using namespace std;
int main () {
    int X, Y;
    double A, B, C, K;
    cout << "Введите целые числа X и Y: ";
    cin >> X >> Y;
    cout << "Введите вещественные числа A, B, C: ";
    cin >> A >> B >> C >>;
    cout << "Введите значение K:";
    cin >> K;
    if (X == Y) {
        X = 0;
        Y = 0;
    } else if (X < Y) {
        X = 0;
    } else  {
        Y = 0;
    }
    if (A != B && B != C && A != C) {
       if (A > C && A > B)
       A -= K;
    } else if (B > A && B > C) {
        B -= K;
    } else {
        C -= K;
    }
    cout << "\nРезультаты : " << endl;
    cout << "X = " << X << endl;
    cout << "Y = " << Y << endl;
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    return 0;
}
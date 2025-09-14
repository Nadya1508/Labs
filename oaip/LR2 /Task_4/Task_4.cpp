#include <iostream>
using namespace std;
int main () {
    int X, Y;
    double A, B, C, K;
    cout << "Введите целые числа X и Y: ";
    cin >> X >> Y;
    cout << "Введите вещественные числа A, B, C: ";
    cin >> A >> B >> C ;
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
       if (A > B && A > C ) {
        A -= K;
       } else if (B > A && B > C) {
        B -= K;
    } else if (C > A && C > B) {
        C -= K;
    }
    cout << "Результаты :\n ";
    cout << "X = " << X << "\n";
    cout << "Y = " << Y << "\n";
    cout << "A = " << A << "\n";
    cout << "B = " << B << "\n";
    cout << "C = " << C << "\n";
    return 0;
}
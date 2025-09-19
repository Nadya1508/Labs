#include <iostream>
using namespace std;
int main () {
    double a, b, c, Y;
    int N;
    cout << "Введите значение a: ";
    cin >> a;
    cout << "Введите значение b: ";
    cin >> b;
    cout << "Введите значение c: ";
    cin >> c;
    cout << "Введите значение N: ";
    cin >> N;
    switch (N) {
        case 2:
          Y = b * c - a * a;
          break;
        case 56:
          Y = b * c;
          break;
        case 7:
          Y = a * a + c;
          break;
        case 3:
          Y = a - b * c;
          break;
        default:
          Y = (a + b) * (a + b) * (a + b);
          break;
    }
    cout << "Результат Y = " << Y << endl;
    return 0;
}
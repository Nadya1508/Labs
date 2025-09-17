#include <iostream>
#include <cmath>
using namespace std;
int main(){
    double x, D;
    cout << "Введите значение x: ";
    cin >> x;
    cout << "Введите значение D: ";
    cin >> D;
    double b = x + D;
    if (b == 0){
        cout << "Ошибка: деление на ноль" << endl;
        return 1;
    }
    double A = (D * x) / b;
    double denominator = pow(D,3) +(A + D - b);
    if (denominator == 0) {
        cout << "Ошибка: знаменатель равен нулю! Деление на ноль невозможно!"<< endl;
        return 1;
    } 
    double numerator = pow(A,2) + b * cos(x);
    double S = numerator /  denominator;
    cout << "\nРезультаты вычислений: " << endl;
    cout << "b = " << b << endl;
    cout << "A = " << A << endl;
    cout << "Числитель = " << numerator << endl;
    cout << "Знаменатель = " << denominator << endl;
    cout << "S = " << S << endl;
    return 0;
}

#include <iostream>
using namespace std;

double sinApprox(double x) {
    double term = x;
    double sum = x;
    double x2 = x * x;
    int sign = -1;

    for ( int i = 3; i <= 13; i +=2){
        term *= x2 / ((i - 1) * i);
        sum += sign * term;
        sign *= -1;
    }
    return sum;
}

double f(double x, int choise) {
    switch(choise) {
        case 1:
        cout << "Выбрана функция f(x) = 2x при x = " << x << endl;
        return 2 * x;
        case 2:
        cout << "Выбрана функция f(x) = x^3 при x = " << x << endl;
        return x * x * x;
        case 3:
        cout << "Выбрана функция f(x) = x / 3 при x = " << x << endl;
        return x / 3.0;
        default :
        cout << "Ошибка: неверный выбор функции. " << endl;
        return 0.0;
    }
}
int main () {
    double z, d;
    int choise;
    cout << "Введите значение z: ";
    cin >> z;
    cout << "Введите значение d: ";
    cin >> d;
    cout << "Выберите функцию: \n1 - f(x) = 2x\n2 - f(x) = x^3\n3 - f(x) = x / 3\nВаш выбор: ";
    cin >> choise;

    double x;
    if (z < 0) {
        x = z * z - z;
        cout << "Условие: z < 0 значит x = z^2 - z = " << x << endl;
    } else {
        x = z * z * z;
        cout << "Условие: z >= 0 значит x = z^3 = " << x << endl;
    }
    double phi = f(x, choise);
    double theta = phi + d * d + x * x;
    cout << "Аргумент синуса θ = f(x) + d^2 + x^2 =  " << theta << endl;

    double sinValue = sinApprox(theta);
    double y = sinValue * sinValue * sinValue;
    cout << "Результат: y = sin³(" << theta << ") ≈ " << y << endl;
    return 0;  
}


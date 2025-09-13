#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main () {
   const int n = 23;
   double b1;
   cout << " Введите первый член геометрической прогрессии b1: ";
   cin >> b1;
   double q = 1 / ( n + 1 );
   if fabs (q) >= 1 {
    cout << " Ошибка: прогрессия не является убывающей ( |q| >= 1) " << endl;
    cout << " q = " << q << endl;
    return 1;
   }

}
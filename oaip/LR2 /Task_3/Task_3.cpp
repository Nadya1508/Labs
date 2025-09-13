#include <iostream>
using namespace std;
int main () {
   const int n = 23;
   double b1;
   cout << " Введите первый член геометрической прогрессии b1: ";
   cin >> b1;
   double q = 1.0 / ( n + 1 );
   if ( q >= 1.0 || q <= -1.0  ) {
    cout << " Ошибка: прогрессия не является убывающей ( |q| >= 1 ) " << endl;
    cout << " q = " << q << endl;
    return 1;
   }
   double sum = b1 / ( n + 1 );
   cout << "/n=== Результаты расчёта ===" << endl;
   cout << "Номер в журнале (n):" << n << endl;
   cout << "Первый член (b1):  " << b1 << endl;
   cout << "Знаменатель (q = 1/(" << n << "+1)):  " << q << endl;
   cout << "Сумма бесконечно убывающей прогресии: " << sum << endl;
   
   return 0;

}
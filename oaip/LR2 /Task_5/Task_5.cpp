#include <iostream>
using namespace std;
int main () {
    double X, Y;
    cout <<"Введите два числа X и Y: ";
    cin >> X >> Y;
    double max = (X > Y) ? X : Y;
    cout <<"Максимум: " << max << endl; 
    return 0;
}
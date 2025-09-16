#include <iostream>
using namespace std;
int main(){
    int h1, min1, h2, min2;
    cout << "Введите время начала решения задач (часы и минуты)";
    cin >> h1 >> min1;
    cout << "Введите время окончания решения задач (часы и минуты)";
    cin >> h2 >> min2;
    int start_minutes = h1 * 60 + min1;
    int end_minutes = h2 * 60 + min2;
}
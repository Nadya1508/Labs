#include <iostream>
int main() {
double X, Y;
std::cout << "Введите два числа X и Y: ";
std::cin >> X >> Y;
bool isXGreater = (X >Y);
double max;
if (isXGreater) {
    max = X;
} else {
    max = Y;
}
std::cout << "Максимум: " << max << std::endl;
return 0;
}
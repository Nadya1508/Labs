#include <iostream>

using namespace std;
 
double square(double x) {
    return x * x;
}
double sqrt_newton(double x) {
    if (x == 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; i++) {
        guess = 0.5 * (guess + x / guess);
    }
    return guess;
}
double distance(double x1, double y1, double x2, double y2){
    return sqrt_newton(square(x2 - x1) + square(y2-y1));
}
double acos_taylor(double x) {
    if (x < -1) x = -1;
    if (x > 1) x = 1;
      
    double result = 1.5707963267948966; 
    double term = x;
    double x_sq = x * x;
    double numerator = x;

    for (int n = 1; n < 20; n++) {
     numerator *= x_sq * (2*n - 1) * (2*n - 1) / (4 * n * n);
     term  = numerator / (2 * n +1);
     result -= term;
    }
    return result;
}
double radiansToDegrees(double radians) {
    return radians * 180.0 / 3.141592653589793;
}

int main () {
    double x1, y1, x2, y2, x3, y3;
    cout << "Введите координаты вершины A(x1 y1): ";
    cin >> x1 >> y1;
    cout << "Введите координаты вершины B(x2 y2): ";
    cin >> x2 >> y2;
    cout << "Введите координаты вершины С(x3 y3): ";
    cin >> x3 >> y3;
    double a = distance(x2, y2, x3, y3);
    double b = distance(x1, y1, x3, y3);
    double c = distance(x1, y1, x2, y2);  
    cout << "\n1. Длины сторон треугольника:" << endl;
    cout << "Сторона a (BC) = " << a << endl;
    cout << "Сторона b (AC) = " << b << endl;
    cout << "Сторона c (AB) = " << c << endl;
     
    double p = (a + b + c) / 2.0;
    double S1 = sqrt_newton(p * (p - a) * (p - b) * (p - c));

    double ha = (2 * S1) / a;
    double hb = (2 * S1) / b;
    double hc = (2 * S1) / c;
    cout << "\n2. Длины высот треугольника:" << endl;
    cout << "Высота ha (к стороне a) = " << ha << endl;
    cout << "Высота hb (к стороне b) = " << hb << endl;
    cout << "Высота hc (к стороне c) = " << hc << endl;

    double ma = 0.5 * sqrt_newton(2 * b * b + 2 * c * c - a * a);
    double mb = 0.5 * sqrt_newton(2 * a * a + 2 * c * c - b * b);
    double mc = 0.5 * sqrt_newton(2 * a * a + 2 * b * b - c * c);
    cout << "\n3. Длины медиан треугольника:" << endl;
    cout << "Медиана ma (к стороне a) = " << ma << endl;
    cout << "Медиана mb (к стороне b) = " << mb << endl;
    cout << "Медиана mc (к стороне c) = " << mc << endl;

    double la = sqrt_newton(b * c * (square(b + c) - a * a)) / (b + c);
    double lb = sqrt_newton(a * c * (square(a +c) - b * b)) / (a + c);
    double lc = sqrt_newton(a * b * (square(a + b) - c * c)) / (a +b);
    cout << "\n4. Длины биссектрис треугольника:" << endl;
    cout << "Биссектриса la (к стороне a) = " << la << endl;
    cout << "Биссектриса lb (к стороне b) = " << lb << endl;
    cout << "Биссектриса lc (к стороне c) = " << lc << endl;

    double cosA = (square(b) + square(c) - square(a)) / (2 * b * c);
    double cosB = (square(a) + square(c) - square(b)) / (2 * a * c);
    double cosC = (square(a) + square(b) - square(c)) / (2 * a * b);

    double angleA_rad = acos_taylor(cosA);
    double angleB_rad = acos_taylor(cosB);
    double angleC_rad = acos_taylor(cosC);

    double angleA_deg = radiansToDegrees(angleA_rad);
    double angleB_deg = radiansToDegrees(angleB_rad);
    double angleC_deg = radiansToDegrees(angleC_rad);
    cout << "\n5. Углы треугольника:" << endl;
    cout << "Угол A (радианы) = " << angleA_rad << ", градусы = " << angleA_deg << endl;
    cout << "Угол B (радианы) = " << angleB_rad << ", градусы = " << angleB_deg << endl;
    cout << "Угол C (радианы) = " << angleC_rad << ", градусы = " << angleC_deg << endl;

    double R = (a * b * c) / (4 * S1);
    double r = S1 / p;
    cout << "\n6. Радиусы окружностей:" << endl;
    cout << "Радиус описанной окружности R = " << R << endl;
    cout << "Радиус вписанной окружности r = " << r << endl;

    const double PI = 3.141592653589793;
    double S_circumscribed = PI * R * R;
    double L_circumscribed = 2 * PI * R;
    double S_inscribed = PI * r * r;
    double L_inscribed = 2 * PI * r;
    cout << "\n7. Параметры окружностей:" << endl;
    cout << "Описанная окружность: площадь = " << S_circumscribed << ", длина = " <<  L_circumscribed << endl;
    cout << "Вписанная окружность: площадь = " << S_inscribed << ", длина = " << L_inscribed << endl;

    double perimeter = a + b + c;
    double S_heron = S1;
    double S_base_height = 0.5 * ha * a;
    double S_coordinates = 0.5 * ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    if (S_coordinates < 0) S_coordinates = -S_coordinates;
    cout << "\n8. Площадь и периметр треугольника:" << endl;
    cout << "Периметр P = " << perimeter << endl;
    cout << "Площадь(формула Герона) = " << S_heron << endl;
    cout << "Площадь треугольника (основание и высота) = " << S_base_height << endl;
    cout << "Площадь треугольника (через координаты) = " << S_coordinates << endl;

    return 0;
}

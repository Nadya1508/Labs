#include <iostream>

using namespace std;

const double PI = 3.14159265358979323846;
const double PI_2 = PI / 2.0;

double square(double x) {
    return x * x;
}

double sqrt_newton(double x) {
    if (x <= 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; ++i)
        guess = 0.5 * (guess + x / guess);
    return guess;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt_newton(square(x2 - x1) + square(y2 - y1));
}

double acos_taylor(double x) {
    if (x < -1.0) x = -1.0;
    if (x > 1.0) x = 1.0;
    if (x == 1.0) return 0.0;
    if (x == -1.0) return PI;

    double result = PI_2;
    double x_sq = square(x);
    double term = x;
    for (int n = 1; n < 30; n++) {
        term *= x_sq * (2*n - 1) * (2*n - 1) / (4.0 * n * n);
        result -= term / (2*n + 1);
    }
    return result;
}

double radiansToDegrees(double radians) {
    return radians * 180.0 / PI;
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    cout << "Введите координаты вершины A(x1 y1): ";
    cin >> x1 >> y1;
    cout << "Введите координаты вершины B(x2 y2): ";
    cin >> x2 >> y2;
    cout << "Введите координаты вершины C(x3 y3): ";
    cin >> x3 >> y3;

    double a = distance(x2, y2, x3, y3); // BC
    double b = distance(x1, y1, x3, y3); // AC
    double c = distance(x1, y1, x2, y2); // AB
    cout << "\n1. Длины сторон треугольника:\n";
    cout << "Сторона a (BC) = " << a << endl;
    cout << "Сторона b (AC) = " << b << endl;
    cout << "Сторона c (AB) = " << c << endl;

    double p = (a + b + c) / 2.0;
    double S1 = sqrt_newton(p * (p - a) * (p - b) * (p - c));

    double ha = (2 * S1) / a;
    double hb = (2 * S1) / b;
    double hc = (2 * S1) / c;
    cout << "\n2. Длины высот треугольника:\n";
    cout << "Высота ha (к стороне a) = " << ha << endl;
    cout << "Высота hb (к стороне b) = " << hb << endl;
    cout << "Высота hc (к стороне c) = " << hc << endl;

    double ma = 0.5 * sqrt_newton(2 * square(b) + 2 * square(c) - square(a));
    double mb = 0.5 * sqrt_newton(2 * square(a) + 2 * square(c) - square(b));
    double mc = 0.5 * sqrt_newton(2 * square(a) + 2 * square(b) - square(c));
    cout << "\n3. Длины медиан треугольника:\n";
    cout << "Медиана ma (к стороне a) = " << ma << endl;
    cout << "Медиана mb (к стороне b) = " << mb << endl;
    cout << "Медиана mc (к стороне c) = " << mc << endl;

    double la = sqrt_newton(b * c * (square(b + c) - square(a))) / (b + c);
    double lb = sqrt_newton(a * c * (square(a + c) - square(b))) / (a + c);
    double lc = sqrt_newton(a * b * (square(a + b) - square(c))) / (a + b);
    cout << "\n4. Длины биссектрис треугольника:\n";
    cout << "Биссектриса la (к стороне a) = " << la << endl;
    cout << "Биссектриса lb (к стороне b) = " << lb << endl;
    cout << "Биссектриса lc (к стороне c) = " << lc << endl;

    double cosA = (square(b) + square(c) - square(a)) / (2 * b * c);
    double cosB = (square(a) + square(c) - square(b)) / (2 * a * c);
    double cosC = (square(a) + square(b) - square(c)) / (2 * a * b);

    double angleA_rad = acos_taylor(cosA);
    double angleB_rad = acos_taylor(cosB);
    double angleC_rad = PI - angleA_rad - angleB_rad;

    double sum_angles = angleA_rad + angleB_rad + angleC_rad;
    cout << "\nСумма углов (радианы): " << sum_angles << endl;
    cout << "Сумма углов (градусы): " << radiansToDegrees(sum_angles) << endl;

    double angleA_deg = radiansToDegrees(angleA_rad);
    double angleB_deg = radiansToDegrees(angleB_rad);
    double angleC_deg = radiansToDegrees(angleC_rad);
    cout << "\n5. Углы треугольника:\n";
    cout << "Угол A = " << angleA_rad << " рад, " << angleA_deg << "°\n";
    cout << "Угол B = " << angleB_rad << " рад, " << angleB_deg << "°\n";
    cout << "Угол C = " << angleC_rad << " рад, " << angleC_deg << "°\n";

    double R = (a * b * c) / (4 * S1);
    double r = S1 / p;
    cout << "\n6. Радиусы окружностей:\n";
    cout << "Радиус описанной окружности R = " << R << endl;
    cout << "Радиус вписанной окружности r = " << r << endl;

    double S_circ = PI * R * R;
    double L_circ = 2 * PI * R;
    double S_in = PI * r * r;
    double L_in = 2 * PI * r;
    cout << "\n7. Параметры окружностей:\n";
    cout << "Описанная: площадь = " << S_circ << ", длина = " << L_circ << endl;
    cout << "Вписанная: площадь = " << S_in << ", длина = " << L_in << endl;

    double perimeter = a + b + c;
    double S_base_height = 0.5 * a * ha;
    double S_coords = 0.5 * ((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1));
    if (S_coords < 0) S_coords = -S_coords;

    cout << "\n8. Площадь и периметр треугольника:\n";
    cout << "Периметр = " << perimeter << endl;
    cout << "Площадь (Герон) = " << S1 << endl;
    cout << "Площадь (основание и высота) = " << S_base_height << endl;
    cout << "Площадь (через координаты) = " << S_coords << endl;

    return 0;
}

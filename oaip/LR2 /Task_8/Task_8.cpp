#include <iostream>
using namespace std;

// Функция для вычисления квадрата числа
double square(double x) {
    return x * x;
}

// Функция для вычисления квадратного корня (метод Ньютона)
double sqrt_newton(double x) {
    if (x <= 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; ++i)
        guess = 0.5 * (guess + x / guess);
    return guess;
}

// Функция для вычисления арктангенса (ряд Тейлора)
double atan_taylor(double x) {
    if (x < -1.0) x = -1.0;
    if (x > 1.0) x = 1.0;
    
    double result = x;
    double term = x;
    double x_sq = x * x;
    
    for (int n = 1; n < 30; n++) {
        term = term * x_sq;
        double denominator = 2 * n + 1;
        if (n % 2 == 0) {
            result = result + term / denominator;
        } else {
            result = result - term / denominator;
        }
    }
    return result;
}

// Функция для вычисления арккосинуса через арктангенс
double acos_via_atan(double x) {
    if (x < -1.0) x = -1.0;
    if (x > 1.0) x = 1.0;
    
    if (x == 1.0) return 0.0;
    if (x == -1.0) return 3.141592653589793;
    
    // acos(x) = 2 * atan(sqrt((1-x)/(1+x)))
    return 2 * atan_taylor(sqrt_newton((1-x)/(1+x)));
}

// Функция для вычисления расстояния между двумя точками
double distance(double x1, double y1, double x2, double y2) {
    return sqrt_newton(square(x2 - x1) + square(y2 - y1));
}

// Константы
const double PI = 3.141592653589793;

// Функция для перевода радиан в градусы
double radiansToDegrees(double radians) {
    return radians * 180.0 / PI;
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    
    cout << "Введите координаты вершины A (x1 y1): ";
    cin >> x1 >> y1;
    
    cout << "Введите координаты вершины B (x2 y2): ";
    cin >> x2 >> y2;
    
    cout << "Введите координаты вершины C (x3 y3): ";
    cin >> x3 >> y3;
    
    // 1. Вычисление длин сторон
    double a = distance(x2, y2, x3, y3); // сторона BC противолежащая A
    double b = distance(x1, y1, x3, y3); // сторона AC противолежащая B
    double c = distance(x1, y1, x2, y2); // сторона AB противолежащая C
    
    cout << "\n1. ДЛИНЫ СТОРОН ТРЕУГОЛЬНИКА:" << endl;
    cout << "Сторона a (BC) = " << a << endl;
    cout << "Сторона b (AC) = " << b << endl;
    cout << "Сторона c (AB) = " << c << endl;
    
    // 2. Вычисление высот
    double p = (a + b + c) / 2.0; // полупериметр
    double S_heron = sqrt_newton(p * (p - a) * (p - b) * (p - c)); // площадь по формуле Герона
    
    double ha = (2 * S_heron) / a; // высота к стороне a
    double hb = (2 * S_heron) / b; // высота к стороне b
    double hc = (2 * S_heron) / c; // высота к стороне c
    
    cout << "\n2. ДЛИНЫ ВЫСОТ ТРЕУГОЛЬНИКА:" << endl;
    cout << "Высота ha (к стороне a) = " << ha << endl;
    cout << "Высота hb (к стороне b) = " << hb << endl;
    cout << "Высота hc (к стороне c) = " << hc << endl;
    
    // 3. Вычисление медиан
    double ma = 0.5 * sqrt_newton(2 * b * b + 2 * c * c - a * a);
    double mb = 0.5 * sqrt_newton(2 * a * a + 2 * c * c - b * b);
    double mc = 0.5 * sqrt_newton(2 * a * a + 2 * b * b - c * c);
    
    cout << "\n3. ДЛИНЫ МЕДИАН ТРЕУГОЛЬНИКА:" << endl;
    cout << "Медиана ma (к стороне a) = " << ma << endl;
    cout << "Медиана mb (к стороне b) = " << mb << endl;
    cout << "Медиана mc (к стороне c) = " << mc << endl;
    
    // 4. Вычисление биссектрис
    double la = sqrt_newton(b * c * (square(b + c) - a * a)) / (b + c);
    double lb = sqrt_newton(a * c * (square(a + c) - b * b)) / (a + c);
    double lc = sqrt_newton(a * b * (square(a + b) - c * c)) / (a + b);
    
    cout << "\n4. ДЛИНЫ БИССЕКТРИС ТРЕУГОЛЬНИКА:" << endl;
    cout << "Биссектриса la (к стороне a) = " << la << endl;
    cout << "Биссектриса lb (к стороне b) = " << lb << endl;
    cout << "Биссектриса lc (к стороне c) = " << lc << endl;
    
    // 5. Вычисление углов (в радианах и градусах)
    double cosA = (b * b + c * c - a * a) / (2 * b * c);
    double cosB = (a * a + c * c - b * b) / (2 * a * c);
    double cosC = (a * a + b * b - c * c) / (2 * a * b);
    
    // Вычисляем углы через арктангенс
    double angleA_rad = acos_via_atan(cosA);
    double angleB_rad = acos_via_atan(cosB);
    double angleC_rad = acos_via_atan(cosC);
    
    // Корректируем сумму углов
    double sum_rad = angleA_rad + angleB_rad + angleC_rad;
    if (sum_rad < PI - 0.01 || sum_rad > PI + 0.01) {
        // Пересчитываем третий угол для гарантии суммы 180°
        angleC_rad = PI - angleA_rad - angleB_rad;
    }
    
    double angleA_deg = radiansToDegrees(angleA_rad);
    double angleB_deg = radiansToDegrees(angleB_rad);
    double angleC_deg = radiansToDegrees(angleC_rad);
    
    cout << "\n5. УГЛЫ ТРЕУГОЛЬНИКА:" << endl;
    cout << "Угол A: " << angleA_rad << " радиан, " << angleA_deg << " градусов" << endl;
    cout << "Угол B: " << angleB_rad << " радиан, " << angleB_deg << " градусов" << endl;
    cout << "Угол C: " << angleC_rad << " радиан, " << angleC_deg << " градусов" << endl;
    cout << "Сумма углов: " << angleA_deg + angleB_deg + angleC_deg << " градусов" << endl;
    
    // 6. Радиусы окружностей
    double R = (a * b * c) / (4 * S_heron); // радиус описанной окружности
    double r = S_heron / p; // радиус вписанной окружности
    
    cout << "\n6. РАДИУСЫ ОКРУЖНОСТЕЙ:" << endl;
    cout << "Радиус описанной окружности R = " << R << endl;
    cout << "Радиус вписанной окружности r = " << r << endl;
    
    // 7. Площадь и длина окружностей
    double S_circumscribed = PI * R * R;
    double L_circumscribed = 2 * PI * R;
    double S_inscribed = PI * r * r;
    double L_inscribed = 2 * PI * r;
    
    cout << "\n7. ПАРАМЕТРЫ ОКРУЖНОСТЕЙ:" << endl;
    cout << "Описанная окружность: площадь = " << S_circumscribed << ", длина = " << L_circumscribed << endl;
    cout << "Вписанная окружность: площадь = " << S_inscribed << ", длина = " << L_inscribed << endl;
    
    // 8. Площадь и периметр треугольника (3 способа)
    double perimeter = a + b + c;
    
    // Способ 1: Формула Герона (уже вычислена)
    // Способ 2: Через основание и высоту
    double S_base_height = 0.5 * a * ha;
    
    // Способ 3: Через координаты (векторное произведение)
    double S_coordinates = 0.5 * ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    if (S_coordinates < 0) S_coordinates = -S_coordinates;
    
    cout << "\n8. ПЛОЩАДЬ И ПЕРИМЕТР ТРЕУГОЛЬНИКА:" << endl;
    cout << "Периметр P = " << perimeter << endl;
    cout << "Площадь (формула Герона) = " << S_heron << endl;
    cout << "Площадь (основание × высота) = " << S_base_height << endl;
    cout << "Площадь (через координаты) = " << S_coordinates << endl;
    
    return 0;
}
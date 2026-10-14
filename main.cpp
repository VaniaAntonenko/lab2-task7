#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Circle {
    double x, y, r;
};

struct Point {
    double x, y;
};

void findOneTangent(Circle c1, Circle c2) {
    double dx = c2.x - c1.x;
    double dy = c2.y - c1.y;

    double d2 = dx * dx + dy * dy;
    double d = sqrt(d2);

    if (d < EPS) {
        if (fabs(c1.r - c2.r) < EPS) {
            cout << "Центри кіл збігаються, радіуси однакові, спільних дотичних безліч\n";
        }else {
            cout << "Центри кіл збігаються, але радіуси різні, тому спільних дотичних не існує";
        }
        return;
    }

    int values[] = {1, -1};
    for (int s : values) {
        double h = c1.r - s * c2.r;

        if (fabs(h) > d + EPS)
            continue;

        double q_sq = max(0.0, d2 - h * h);
        double q = sqrt(q_sq);

        int signs = (q < EPS) ? 1 : 2;

        for (int i = 0; i < signs; i++) {
            int sign = (i == 0) ? 1 : -1;

            // Координати одиничного вектора нормалі до дотичної
            double nx = (h * dx - sign * q * dy) / d2;
            double ny = (h * dy + sign * q * dx) / d2;

            // Точки дотику
            Point p1 = { c1.x + c1.r * nx,     c1.y + c1.r * ny };
            Point p2 = { c2.x + s * c2.r * nx, c2.y + s * c2.r * ny };

            cout << fixed << setprecision(3);
            cout << "\nЗнайдено спільну дотичну лінію:\n";
            cout << "  Точка дотику на першому колі: (" << p1.x << ", " << p1.y << ")\n";
            cout << "  Точка дотику на другому колі: (" << p2.x << ", " << p2.y << ")\n";

            return; // Виходимо з функції одразу після знаходження першої дотичної
        }
    }

    cout << "Спільних дотичних немає\n";
}

int main() {
    Circle c1, c2;

    cout << "Введіть x1 y1 r1 для першого кола: ";
    cin >> c1.x >> c1.y >> c1.r;

    cout << "Введіть x2 y2 r2 для другого кола: ";
    cin >> c2.x >> c2.y >> c2.r;

    if (c1.r < 0 || c2.r < 0) {
        cout << "Помилка: радіус не може бути від'ємним\n";
        return 1;
    }

    findOneTangent(c1, c2);

    return 0;
}
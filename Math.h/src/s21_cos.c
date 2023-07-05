#include "s21_math.h"

long double s21_cos(double x) {
    int z = s21_fabs(x) / s21_P, k = x < 0 ? -1 : 1;
    z > 1 ? x -= (s21_P * z) * k : 0;
    double y = 1;
    double s = -1;
    for (int i = 2; i <= 100; i += 2) {
        y += s * (my_pow(x, i) / s21_fact(i));
        s *= -1;
    }
    return z == 1 ? y : z % 2 == 0 ? y : -y;
}

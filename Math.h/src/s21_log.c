#include "s21_math.h"

long double s21_log(double x) {
    long double gr = 0, temp = 0, result = 0, z = 2, m = x < 0 ? 1 : x == 0 ? 2 : 0;
    while (((x >= 10) || (x < 1 && x > 0)) && m == 0)
        x < 1 && x > 0 ? (x *= 10.l, gr -= 1) : (x *= 0.1, gr += 1);
    x /= 10.l;
    for (x--, result = x, temp = x; m == 0 &&
        s21_fabs(result) > ACC; result *= -x * (z - 1) / z, z++, temp += result) {}
    return m == 1 ? S21_NAN : m == 2 ? -S21_INF : temp + (gr + 1) * S21_LN10;
}

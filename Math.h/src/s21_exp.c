#include "s21_math.h"

long double my_exp(double x, long double s, long double n, long double a) {
    a = a * x / n;
    return s21_fabs(a) <= ACC ? s : my_exp(x, s + a, n + 1, a);
}

long double s21_exp(double x) {
    long double s = 1;
    long double n = 1;
    long double a = 1;
    return x != x ? S21_NAN : my_exp(x, s, n, a);
}

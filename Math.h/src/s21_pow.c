#include "s21_math.h"

long double s21_pow(double base, double exp) {
    long double res = (exp == (int)exp && exp > 0 ? my_pow(base, exp) : exp == 0 ?
                        1.l : exp == 1 ? base : base < 0 && exp != (int)exp ? S21_NAN : 0);
    int r = base < 0 && (int)exp % 2 != 0 ? -1 : 1;
    int g = base < 0 ? -1 : 1, t = exp < 0 ? -1 : 1;
    if (res == 0) {
        res = r * s21_exp((exp * t) * s21_log(base * g));
        t < 0 ? res = 1.l / res : 0;
    }
    return res;
}

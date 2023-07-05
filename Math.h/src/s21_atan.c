#include "s21_math.h"

long double s21_atan(double x) {
    int neg = 0, per = 0, sp = 0;
    x < 0.l ? x = -x, neg = 1 : 0;
    x > 1.l ? x = (1.l / x), per = 1 : 0;
    while (x > s21_P / 12.l) {
        sp++;
        x = ((x * s21_sqrt(3)) - 1.l) * (1.l / (x + s21_sqrt(3)));
    }
    x = x * ((0.55913709l / (1.4087812l + x * x)) + 0.60310579l - 0.05160454l * (x * x));
    while (sp > 0) {
        x += (s21_P_6);
        sp--;
    }
    x = per ? (s21_P_2) - x : x;
    x = neg ? -x : x;
    return x;
}

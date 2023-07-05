#include "s21_math.h"

void mfp(double x, double y, double *buf) {
    while (*buf <= x) *buf += y;
    *buf -= y;
}

long double my_fmod(double x, double y, double buf) {
    if (x < 0) { buf = s21_fabs(buf);
        y = s21_fabs(y);
        x = s21_fabs(x);
        mfp(x, y, &buf);
        buf = (x - buf) * -1;
    } else {  buf = s21_fabs(buf);
        y = s21_fabs(y);
        x = s21_fabs(x);
        mfp(x, y, &buf);
        buf = x - buf;
    }
    return buf;
}

long double s21_fmod(double x, double y) {
    long double res = 0.0;
    if (x != x || y != y || y == 0.0) { res = S21_NAN;
    } else if (y > x && x > 0) { res = x;
    } else if (y == x) { res = 0.0;
    } else { double buf = y;
        res = my_fmod(x, y, buf);
    }
    return res;
}

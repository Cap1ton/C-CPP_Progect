#include "s21_math.h"

long double s21_floor(double x) {
    int y = x + 0;
    return y == x ? y : y < x ? (long double)y : (long double)y - 1;
}

#include "s21_math.h"

long double s21_fabs(double num) {
    return num < 0 ? num * -1 : num;
}

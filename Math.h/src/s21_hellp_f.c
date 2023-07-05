#include "s21_math.h"

long double s21_fact(long double x) {
    return x > 1.0 ? x * s21_fact(x - 1) : 1.0;
}

long double my_pow(long double base, long int exp) {
    return exp > 0 ? base * my_pow(base, exp - 1) : 1;
}

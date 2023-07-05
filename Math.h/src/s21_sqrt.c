#include "s21_math.h"

long double s21_sqrt(double x) {
    long double squareRoot = 0.0;
    long double t = squareRoot;
    if (x > 0) {
        squareRoot = x / 2.0;
    do {
        t = squareRoot;
        squareRoot = (t + (x / t)) / 2.0;
    } while ((t - squareRoot) != 0);
    } else if (x < 0) {
        squareRoot = S21_NAN;
    }
    return squareRoot;
}

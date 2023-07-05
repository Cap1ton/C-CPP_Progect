#ifndef SRC_SRC_S21_MATH_H_
#define SRC_SRC_S21_MATH_H_
#include <stdio.h>

#define S21_LN10 2.30258509299404568401799145468436421
#define s21_PI 3.141592653589793238462643383279502884197169399375105820974944
#define s21_E 2.718281828459045235360287471352662497757247093699959574966967
#define S21_NAN 0.0/0.0
#define S21_INF 1.F/0.0
#define ACC 1e-17l
#define s21_P_6 0.52359877559
#define s21_P_4 0.78539816339
#define s21_P_3 1.0471975512
#define s21_P_2 1.57079632679
#define s21_2P_3 2.09439510239
#define s21_3P_4 2.35619449019
#define s21_5P_6 2.61799387799
#define s21_P 3.14159265358
#define s21_7P_6 3.66519142919
#define s21_5P_4 3.92699081699
#define s21_4P_3 4.18879020479
#define s21_3P_2 4.71238898038
#define s21_5P_3 5.23598775598
#define s21_7P_4 5.49778714378
#define s21_11P_6 5.75958653158
#define s21_5P_3 5.23598775598
#define s21_2P 6.28318530718

long double my_sqrt_exp(long int xp, long double res); // Степень корня

long double my_pow(long double base, long int exp); // Степень целочисленая

long double s21_fact(long double x); // Факториал числа

int s21_abs(int num); // Модуль целого числа

long double s21_acos(double x);

long double s21_asin(double x);

long double s21_atan(double x);

long double s21_ceil(double x);

long double s21_cos(double x);

long double s21_exp(double x); // экспонента

long double s21_fabs(double num);  // Модуль дробного числа

long double s21_floor(double x);

long double s21_fmod(double x, double y); // Остаток от деления дробного числа

long double s21_log(double x); // Натуральный лагорифм числа

long double s21_pow(double base, double exp); // Дробная степень

long double s21_sin(double x);

long double s21_sqrt(double x);

long double s21_tan(double x);

#endif //  SRC_SRC_S21_MATH_H_
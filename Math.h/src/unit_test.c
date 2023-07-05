#include "s21_math.h"
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>


START_TEST(s21_absTEST) {  // тест кейс с 10 -> с 15
    ck_assert_int_eq(s21_abs(-1), abs(-1));
    ck_assert_int_eq(s21_abs(5), abs(5));
    ck_assert_int_eq(s21_abs(-2147483647), abs(-2147483647));
    ck_assert_int_eq(s21_abs(-0xA13), abs(-0xA13));
    ck_assert_int_eq(s21_abs(13), abs(13));
    ck_assert_int_eq(s21_abs(-0), abs(-0));
    ck_assert_int_eq(s21_abs(-05), abs(-05));
    ck_assert_int_eq(s21_abs(-00002345670), abs(-00002345670));
    ck_assert_int_eq(s21_abs(123456789), abs(123456789));
    ck_assert_int_eq(s21_abs(100), abs(100));
    ck_assert_int_eq(s21_abs(-100), abs(-100));
    ck_assert_int_eq(s21_abs(0), abs(0));
}
END_TEST

START_TEST(s21_cosTEST) {
    ck_assert_double_eq_tol(s21_cos(-1), cos(-1), 1e-6);
    ck_assert_double_eq_tol(s21_cos(1), cos(1), 1e-6);
    ck_assert_double_eq_tol(s21_cos(10), cos(10), 1e-6);
    ck_assert_double_eq_tol(s21_cos(0), cos(0), 1e-6);
    ck_assert_double_eq_tol(s21_cos(0x14BD), cos(0x14BD), 1e-6);
    ck_assert_double_eq_tol(s21_cos(145), cos(145), 1e-6);
    ck_assert_double_eq_tol(s21_cos(16), cos(16), 1e-6);
    ck_assert_double_eq_tol(s21_cos(5), cos(5), 1e-6);
    ck_assert_double_eq_tol(s21_cos(7), cos(7), 1e-6);
    ck_assert_double_eq_tol(s21_cos(-16), cos(-16), 1e-6);
    ck_assert_double_eq_tol(s21_cos(145986), cos(145986), 1e-6);
    ck_assert_int_eq(isnan(s21_cos(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_sinTEST) {
    ck_assert_double_eq_tol(s21_sin(-1), sin(-1), 1e-6);
    ck_assert_double_eq_tol(s21_sin(1), sin(1), 1e-6);
    ck_assert_double_eq_tol(s21_sin(10), sin(10), 1e-6);
    ck_assert_double_eq_tol(s21_sin(0), sin(0), 1e-6);
    ck_assert_double_eq_tol(s21_sin(0x14BD), sin(0x14BD), 1e-6);
    ck_assert_double_eq_tol(s21_sin(145), sin(145), 1e-6);
    ck_assert_double_eq_tol(s21_sin(16), sin(16), 1e-6);
    ck_assert_double_eq_tol(s21_sin(5), sin(5), 1e-6);
    ck_assert_double_eq_tol(s21_sin(7), sin(7), 1e-6);
    ck_assert_double_eq_tol(s21_sin(-16), sin(-16), 1e-6);
    ck_assert_double_eq_tol(s21_sin(145986), sin(145986), 1e-6);
    ck_assert_int_eq(isnan(s21_sin(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_tanTEST) {
    ck_assert_double_eq_tol(s21_tan(-1), tan(-1), 1e-6);
    ck_assert_double_eq_tol(s21_tan(1), tan(1), 1e-6);
    ck_assert_double_eq_tol(s21_tan(10), tan(10), 1e-6);
    ck_assert_double_eq_tol(s21_tan(0), tan(0), 1e-6);
    ck_assert_double_eq_tol(s21_tan(0x14BD), tan(0x14BD), 1e-6);
    ck_assert_double_eq_tol(s21_tan(145), tan(145), 1e-6);
    ck_assert_double_eq_tol(s21_tan(16), tan(16), 1e-6);
    ck_assert_double_eq_tol(s21_tan(-16), tan(-16), 1e-6);
    ck_assert_int_eq(isnan(s21_tan(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_acosTEST) {
    ck_assert_double_eq_tol(s21_acos(-1), acos(-1), 1e-6);
    ck_assert_double_eq_tol(s21_acos(1), acos(1), 1e-6);
    ck_assert_double_eq_tol(s21_acos(0.2), acos(0.2), 1e-6);
    ck_assert_int_eq(isnan(s21_acos(2)), 1);
    ck_assert_double_eq_tol(s21_acos(0), acos(0), 1e-6);
    ck_assert_int_eq(isnan(s21_acos(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_asinTEST) {
    ck_assert_double_eq_tol(s21_asin(-1), asin(-1), 1e-6);
    ck_assert_double_eq_tol(s21_asin(1), asin(1), 1e-6);
    ck_assert_double_eq_tol(s21_asin(0.2), asin(0.2), 1e-6);
    ck_assert_int_eq(isnan(s21_asin(2)), 1);
    ck_assert_double_eq_tol(s21_asin(0), asin(0), 1e-6);
    ck_assert_int_eq(isnan(s21_asin(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_atanTEST) {
    ck_assert_double_eq_tol(s21_atan(-1), atan(-1), 1e-6);
    ck_assert_double_eq_tol(s21_atan(1), atan(1), 1e-6);
    ck_assert_double_eq_tol(s21_atan(10), atan(10), 1e-6);
    ck_assert_double_eq_tol(s21_atan(0x14BD), atan(0x14BD), 1e-6);
    ck_assert_double_eq_tol(s21_atan(0), atan(0), 1e-6);
    ck_assert_double_eq_tol(s21_atan(145), atan(145), 1e-6);
    ck_assert_double_eq_tol(s21_atan(16), atan(16), 1e-6);
    ck_assert_double_eq_tol(s21_atan(145986), atan(145986), 1e-6);
    ck_assert_int_eq(isnan(s21_atan(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_expTEST) {
    ck_assert_double_eq_tol(s21_exp(1), exp(1), 1e-6);
    ck_assert_double_eq_tol(s21_exp(10), exp(10), 1e-6);
    ck_assert_double_eq_tol(s21_exp(100), exp(100), 1e-6);
    ck_assert_double_eq_tol(s21_exp(178), exp(178), 1e-6);
    ck_assert_double_eq_tol(s21_exp(0), exp(0), 1e-6);
    ck_assert_double_eq_tol(s21_exp(12), exp(12), 1e-6);
    ck_assert_double_eq_tol(s21_exp(-1), exp(-1), 1e-6);
    ck_assert_int_eq(isnan(s21_exp(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_logTEST) {
    ck_assert_double_eq_tol(s21_log(1), log(1), 1e-6);
    ck_assert_double_eq_tol(s21_log(10), log(10), 1e-6);
    ck_assert_double_eq_tol(s21_log(100), log(100), 1e-6);
    ck_assert_double_eq_tol(s21_log(0x14BD), log(0x14BD), 1e-6);
    ck_assert_int_eq(isinf(s21_log(0)), 1);
    ck_assert_double_eq_tol(s21_log(12), log(12), 1e-6);
    ck_assert_int_eq(isnan(s21_log(-1)), 1);
    ck_assert_int_eq(isnan(s21_log(S21_NAN)), 1);
}
END_TEST

START_TEST(s21_powTEST) {
    ck_assert_double_eq_tol(s21_pow(1, 2), pow(1, 2), 1e-6);
    ck_assert_double_eq_tol(s21_pow(0, 0), pow(0, 0), 1e-6);
    ck_assert_double_eq_tol(s21_pow(12, 0), pow(12, 0), 1e-6);
    ck_assert_double_eq_tol(s21_pow(-1, 2), pow(-1, 2), 1e-6);
    ck_assert_double_eq_tol(s21_pow(-15, 3), pow(-15, 3), 1e-6);
    ck_assert_double_eq_tol(s21_pow(-15, -3), pow(-15, -3), 1e-6);
    ck_assert_double_eq_tol(s21_pow(15, -3), pow(15, -3), 1e-6);
    ck_assert_double_eq_tol(s21_pow(15, -3.45), pow(15, -3.45), 1e-6);
    ck_assert_int_eq(isnan(s21_pow(-15, 3.45)), 1);
    ck_assert_int_eq(isnan(s21_pow(-15, -3.45)), 1);
    ck_assert_double_eq_tol(s21_pow(23, 10), pow(23, 10), 1e+0);
    ck_assert_double_eq_tol(s21_pow(10, 100), powl(10, 100), 1e+0);
}
END_TEST

START_TEST(s21_sqrtTEST) {
    ck_assert_double_eq_tol(s21_sqrt(1), sqrt(1), 1e-6);
    ck_assert_double_eq_tol(s21_sqrt(10), sqrt(10), 1e-6);
    ck_assert_double_eq_tol(s21_sqrt(100), sqrt(100), 1e-6);
    ck_assert_double_eq_tol(s21_sqrt(178), sqrt(178), 1e-6);
    ck_assert_double_eq_tol(s21_sqrt(0), sqrt(0), 1e-6);
    ck_assert_double_eq_tol(s21_sqrt(12), sqrt(12), 1e-6);
    ck_assert_int_eq(isnan(s21_sqrt(-1)), 1);
}
END_TEST

START_TEST(s21_ceilTEST) {
    ck_assert_double_eq_tol(s21_ceil(1.2), ceil(1.2), 1e-6);
    ck_assert_double_eq_tol(s21_ceil(10.978567), ceil(10.978567), 1e-6);
    ck_assert_double_eq_tol(s21_ceil(-12.23), ceil(-12.23), 1e-6);
    ck_assert_double_eq_tol(s21_ceil(12), ceil(12), 1e-6);
    ck_assert_double_eq_tol(s21_ceil(0), ceil(0), 1e-6);
}
END_TEST

START_TEST(s21_fabsTEST) {
    ck_assert_double_eq_tol(s21_fabs(-11245123.23), fabs(-11245123.23), 1e-6);
    ck_assert_double_eq_tol(s21_fabs(1023.l), fabs(1023.f), 1e-6);
    ck_assert_double_eq_tol(s21_fabs(0.l), fabs(0.f), 1e-6);
    ck_assert_double_eq_tol(s21_fabs(-12.456), fabs(-12.456), 1e-6);
    ck_assert_double_eq_tol(s21_fabs(-1.1), fabs(-1.1), 1e-6);
}
END_TEST

START_TEST(s21_floorTEST) {
    ck_assert_double_eq_tol(s21_floor(1.2), floor(1.2), 1e-6);
    ck_assert_double_eq_tol(s21_floor(10.978567), floor(10.978567), 1e-6);
    ck_assert_double_eq_tol(s21_floor(-12.23), floor(-12.23), 1e-6);
    ck_assert_double_eq_tol(s21_floor(12), floor(12), 1e-6);
    ck_assert_double_eq_tol(s21_floor(0), floor(0), 1e-6);
}
END_TEST

START_TEST(s21_fmodTEST) {
    ck_assert_double_eq_tol(s21_fmod(1, 2), fmod(1, 2), 1e-6);
    ck_assert_double_eq_tol(s21_fmod(145.4673, 12.3), fmod(145.4673, 12.3), 1e-6);
    ck_assert_int_eq(isnan(s21_fmod(1, 0)), 1);
    ck_assert_double_eq_tol(s21_fmod(4, 2), fmod(4, 2), 1e-6);
    ck_assert_double_eq_tol(s21_fmod(0, 1), fmod(0, 1), 1e-6);
    ck_assert_double_eq_tol(s21_fmod(-12.67, 3.4), fmod(-12.67, 3.4), 1e-6);
}
END_TEST

int main(void) {
    Suite *suite = suite_create("S21_Debuger");
    SRunner *srunner = srunner_create(suite);

    TCase *s21_abs_p = tcase_create("s21_abs");
    suite_add_tcase(suite, s21_abs_p);
    tcase_add_test(s21_abs_p, s21_absTEST);

    TCase *s21_cos_p = tcase_create("s21_cos");
    suite_add_tcase(suite, s21_cos_p);
    tcase_add_test(s21_cos_p, s21_cosTEST);

    TCase *s21_sin_p = tcase_create("s21_sin");
    suite_add_tcase(suite, s21_sin_p);
    tcase_add_test(s21_sin_p, s21_sinTEST);

    TCase *s21_tan_p = tcase_create("s21_tan");
    suite_add_tcase(suite, s21_tan_p);
    tcase_add_test(s21_tan_p, s21_tanTEST);

    TCase *s21_acos_p = tcase_create("s21_acos");
    suite_add_tcase(suite, s21_acos_p);
    tcase_add_test(s21_acos_p, s21_acosTEST);

    TCase *s21_asin_p = tcase_create("s21_asin");
    suite_add_tcase(suite, s21_asin_p);
    tcase_add_test(s21_asin_p, s21_asinTEST);

    TCase *s21_atan_p = tcase_create("s21_atan");
    suite_add_tcase(suite, s21_atan_p);
    tcase_add_test(s21_atan_p, s21_atanTEST);

    TCase *s21_exp_p = tcase_create("s21_exp");
    suite_add_tcase(suite, s21_exp_p);
    tcase_add_test(s21_exp_p, s21_expTEST);

    TCase *s21_log_p = tcase_create("s21_log");
    suite_add_tcase(suite, s21_log_p);
    tcase_add_test(s21_log_p, s21_logTEST);

    TCase *s21_pow_p = tcase_create("s21_pow");
    suite_add_tcase(suite, s21_pow_p);
    tcase_add_test(s21_pow_p, s21_powTEST);

    TCase *s21_sqrt_p = tcase_create("s21_sqrt");
    suite_add_tcase(suite, s21_sqrt_p);
    tcase_add_test(s21_sqrt_p, s21_sqrtTEST);

    TCase *s21_ceil_p = tcase_create("s21_ceil");
    suite_add_tcase(suite, s21_ceil_p);
    tcase_add_test(s21_ceil_p, s21_ceilTEST);

    TCase *s21_fabs_p = tcase_create("s21_fabs");
    suite_add_tcase(suite, s21_fabs_p);
    tcase_add_test(s21_fabs_p, s21_fabsTEST);

    TCase *s21_floor_p = tcase_create("s21_floor");
    suite_add_tcase(suite, s21_floor_p);
    tcase_add_test(s21_floor_p, s21_floorTEST);

    TCase *s21_fmod_p = tcase_create("s21_fmod");
    suite_add_tcase(suite, s21_fmod_p);
    tcase_add_test(s21_fmod_p, s21_fmodTEST);

    srunner_run_all(srunner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

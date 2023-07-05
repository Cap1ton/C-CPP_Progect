#include <string.h>
#include <stdio.h>
#include <check.h>
#include "SmartCalc/pol/pol.h" 
#define EPS 1e-7


START_TEST(arifmetic) {
    const char *buf = {" (2+3)*5^2"};
    int error_target = 0;
    double result = pol_hendler(buf, 0, &error_target);
    ck_assert_double_eq(result, 125.0);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(Hard_arifmetic) {
    const char *buf = {" 15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))"};
    int error_target = 0;
    double result = pol_hendler(buf, 0, &error_target);
    ck_assert_float_eq_tol(-30.0721649, result, EPS);
    ck_assert_int_eq(error_target, 0);
}
END_TEST


START_TEST(tojdestva) {
    char *buf = {" sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)"};
    int error_target = 0;
    double result = pol_hendler(buf, 0, &error_target);
    ck_assert_int_eq(error_target, 0);
    ck_assert_float_lt(EPS, fabs(-1.47532 - result));
}
END_TEST

START_TEST(radical) {
    const char *buf = {" 2^3^3"};
    int error_target = 0;
    double result = pol_hendler(buf, 0, &error_target);
    ck_assert_double_eq(result, 134217728);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(unari_arifmetic) {
    const char *buf = {" -23*(16+27/2)"};
    int error_target = 0;
    float result = pol_hendler(buf, 0, &error_target);
    ck_assert_float_eq( -678.5, result);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(unari_tojdestva) {
    const char *buf = {" -cos(tan(56-34)/2)"};
    int error_target = 0;
    double result = pol_hendler(buf, 0, &error_target);
    ck_assert_float_eq(0.9999902, result);
    ck_assert_int_eq(error_target, 0);
}
END_TEST




Suite *calculate_tests_create() {
    Suite *calculate = suite_create("calculate");
    TCase *calculate_tests = tcase_create("calculate");
    tcase_add_test(calculate_tests, arifmetic);
    tcase_add_test(calculate_tests, Hard_arifmetic);
    tcase_add_test(calculate_tests, tojdestva);
    tcase_add_test(calculate_tests, radical);
    tcase_add_test(calculate_tests, unari_arifmetic);
    tcase_add_test(calculate_tests, unari_tojdestva);
    suite_add_tcase(calculate, calculate_tests);
    return calculate;
}

int main() {
    Suite *calculate = calculate_tests_create();
    SRunner *calculate_runner = srunner_create(calculate);
    int number_failed;
    srunner_run_all(calculate_runner, FP_NORMAL);
    number_failed = srunner_ntests_failed(calculate_runner);
    srunner_free(calculate_runner);

    return number_failed == 0 ? 0 : 1;
}
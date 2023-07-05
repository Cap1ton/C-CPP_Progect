#include <check.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_1) {
  matrix_t mtrix_1;
  int row = 3, columns = 3, error_target = 0;
  error_target = s21_create_matrix(row, columns, &mtrix_1);
  ck_assert_int_eq(error_target, 0);
  s21_remove_matrix(&mtrix_1);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t mtrix_1;
  int row = 3, columns = 0, error_target = 0;
  error_target = s21_create_matrix(row, columns, &mtrix_1);
  ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t mtrix_1;
  int row = 0, columns = 3, error_target = 0;
  error_target = s21_create_matrix(row, columns, &mtrix_1);
  ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t mtrix_1;
  int row = 0, columns = 0, error_target = 0;
  error_target = s21_create_matrix(row, columns, &mtrix_1);
  ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(s21_create_matrix_5) {
  matrix_t mtrix_1;
  int row = -3, columns = 3, error_target = 0;
  error_target = s21_create_matrix(row, columns, &mtrix_1);
  ck_assert_int_eq(error_target, 1);
}
END_TEST

START_TEST(s21_create_matrix_6) {
  matrix_t mtrix_1;
  int row = 3, columns = -3, error_target = 0;
  error_target = s21_create_matrix(row, columns, &mtrix_1);
  ck_assert_int_eq(error_target, 1);
}
END_TEST

START_TEST(s21_remove_matrix_1) {
  matrix_t matrix_1;
  int row = 3, columns = 3;
  s21_create_matrix(row, columns, &matrix_1);
  s21_remove_matrix(&matrix_1);
  ck_assert_int_eq(matrix_1.rows, 0);
  ck_assert_int_eq(matrix_1.columns, 0);
  int r = matrix_1.matrix == NULL;
  ck_assert_int_eq(r, 1);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
  matrix_t matrix_A, matrix_B;
  int eerror_target = 0;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_B);
  matrix_B.matrix[0][0] = 13E-8;
  matrix_A.matrix[0][0] = 1E-7;
  eerror_target = s21_eq_matrix(&matrix_A, &matrix_B);
  ck_assert_int_eq(eerror_target, 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t matrix_A, matrix_B;
  int eerror_target = 0;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_B);
  eerror_target = s21_eq_matrix(&matrix_A, &matrix_B);
  ck_assert_int_eq(eerror_target, 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t matrix_A, matrix_B;
  int eerror_target = 0;
  s21_create_matrix(3, 4, &matrix_A);
  s21_create_matrix(3, 3, &matrix_B);
  matrix_B.matrix[0][0] = 13E-8;
  matrix_A.matrix[0][0] = 1E-7;
  eerror_target = s21_eq_matrix(&matrix_A, &matrix_B);
  ck_assert_int_eq(eerror_target, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  matrix_t matrix_A, matrix_B;
  int eerror_target = 0;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_B);
  matrix_B.matrix[0][0] = 13;
  eerror_target = s21_eq_matrix(&matrix_A, &matrix_B);
  ck_assert_int_eq(eerror_target, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  matrix_t matrix_A, matrix_B;
  int eerror_target = 0;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_B);
  matrix_B.matrix[0][0] = 1E-7;
  matrix_A.matrix[0][0] = 1E-7;
  eerror_target = s21_eq_matrix(&matrix_A, &matrix_B);
  ck_assert_int_eq(eerror_target, 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(s21_sum_matrix_1) {
  matrix_t matrix_AA, matrix_BB, res1;
  int error_target = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 3, &matrix_AA);
  s21_create_matrix(3, 3, &matrix_BB);
  for (int i = 0; i < matrix_AA.rows; i++) {
    for (int j = 0; j < matrix_AA.columns; j++) {
      matrix_AA.matrix[i][j] = (rand_r(&new) % 10);
      matrix_BB.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target = s21_sum_matrix(&matrix_AA, &matrix_BB, &res1);
  ck_assert_int_eq(error_target, 0);
  s21_remove_matrix(&matrix_AA);
  s21_remove_matrix(&matrix_BB);
  s21_remove_matrix(&res1);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t matrix_AA, matrix_BB, res1;
  int error_target = 0;
  s21_create_matrix(0, 0, &matrix_AA);
  s21_create_matrix(3, 3, &matrix_BB);
  error_target = s21_sum_matrix(&matrix_AA, &matrix_BB, &res1);
  ck_assert_int_eq(error_target, 2);
  s21_remove_matrix(&matrix_BB);
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  matrix_t matrix_AA, matrix_BB, res1;
  int error_target = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 4, &matrix_AA);
  s21_create_matrix(3, 3, &matrix_BB);
  for (int i = 0; i < matrix_AA.rows; i++) {
    for (int j = 0; j < matrix_AA.columns; j++) {
      matrix_AA.matrix[i][j] = (rand_r(&new) % 10);
      matrix_BB.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target = s21_sum_matrix(&matrix_AA, &matrix_BB, &res1);
  ck_assert_int_eq(error_target, 2);
  s21_remove_matrix(&matrix_AA);
  s21_remove_matrix(&matrix_BB);
}
END_TEST

START_TEST(s21_sub_matrix_1) {
  matrix_t matrix_Am, matrix_Bm, res1m;
  int error_targetm = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 3, &matrix_Am);
  s21_create_matrix(3, 3, &matrix_Bm);
  for (int i = 0; i < matrix_Am.rows; i++) {
    for (int j = 0; j < matrix_Am.columns; j++) {
      matrix_Am.matrix[i][j] = (rand_r(&new) % 10);
      matrix_Bm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetm = s21_sub_matrix(&matrix_Am, &matrix_Bm, &res1m);
  ck_assert_int_eq(error_targetm, 0);
  s21_remove_matrix(&matrix_Am);
  s21_remove_matrix(&matrix_Bm);
  s21_remove_matrix(&res1m);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t matrix_Am, matrix_Bm, res1m;
  int error_targetm = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 4, &matrix_Am);
  s21_create_matrix(3, 3, &matrix_Bm);
  for (int i = 0; i < matrix_Am.rows; i++) {
    for (int j = 0; j < matrix_Am.columns; j++) {
      matrix_Am.matrix[i][j] = (rand_r(&new) % 10);
      matrix_Bm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetm = s21_sub_matrix(&matrix_Am, &matrix_Bm, &res1m);
  ck_assert_int_eq(error_targetm, 2);
  s21_remove_matrix(&matrix_Am);
  s21_remove_matrix(&matrix_Bm);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  matrix_t matrix_Am, matrix_Bm, res1m;
  int error_targetm = 0;
  s21_create_matrix(0, 3, &matrix_Am);
  s21_create_matrix(0, 3, &matrix_Bm);
  error_targetm = s21_sub_matrix(&matrix_Am, &matrix_Bm, &res1m);
  ck_assert_int_eq(error_targetm, 1);
}
END_TEST

START_TEST(s21_mult_number_1) {
  matrix_t matrix_Au, res1u;
  int error_targetu = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 3, &matrix_Au);
  for (int i = 0; i < matrix_Au.rows; i++) {
    for (int j = 0; j < matrix_Au.columns; j++) {
      matrix_Au.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetu = s21_mult_number(&matrix_Au, (rand_r(&new) % 10), &res1u);
  ck_assert_int_eq(error_targetu, 0);
  s21_remove_matrix(&matrix_Au);
  s21_remove_matrix(&res1u);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t matrix_Au, res1u;
  int error_targetu = 0;
  unsigned int new = 0;
  s21_create_matrix(0, 0, &matrix_Au);
  error_targetu = s21_mult_number(&matrix_Au, (rand_r(&new) % 10), &res1u);
  ck_assert_int_eq(error_targetu, 1);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t matrix_Amm, matrix_Bmm, res1mm;
  int error_targetmm = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 5, &matrix_Amm);
  s21_create_matrix(5, 3, &matrix_Bmm);
  for (int i = 0; i < matrix_Amm.rows; i++) {
    for (int j = 0; j < matrix_Amm.columns; j++) {
      matrix_Amm.matrix[i][j] = (rand_r(&new) % 10);
      matrix_Bmm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetmm = s21_mult_matrix(&matrix_Amm, &matrix_Bmm, &res1mm);
  ck_assert_int_eq(error_targetmm, 0);
  s21_remove_matrix(&matrix_Amm);
  s21_remove_matrix(&matrix_Bmm);
  s21_remove_matrix(&res1mm);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t matrix_Amm, matrix_Bmm, res1mm;
  int error_targetmm = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 5, &matrix_Amm);
  s21_create_matrix(6, 4, &matrix_Bmm);
  for (int i = 0; i < matrix_Amm.rows; i++) {
    for (int j = 0; j < matrix_Amm.columns; j++) {
      matrix_Amm.matrix[i][j] = (rand_r(&new) % 10);
      matrix_Bmm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetmm = s21_mult_matrix(&matrix_Amm, &matrix_Bmm, &res1mm);
  ck_assert_int_eq(error_targetmm, 2);
  s21_remove_matrix(&matrix_Amm);
  s21_remove_matrix(&matrix_Bmm);
}

START_TEST(s21_mult_matrix_3) {
  matrix_t matrix_Amm, matrix_Bmm, res1mm;
  int error_targetmm = 0;
  unsigned int new = 0;
  s21_create_matrix(0, 0, &matrix_Amm);
  s21_create_matrix(5, 3, &matrix_Bmm);
  for (int i = 0; i < matrix_Amm.rows; i++) {
    for (int j = 0; j < matrix_Amm.columns; j++) {
      matrix_Bmm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetmm = s21_mult_matrix(&matrix_Amm, &matrix_Bmm, &res1mm);
  ck_assert_int_eq(error_targetmm, 2);
  s21_remove_matrix(&matrix_Bmm);
}

START_TEST(s21_transpose_1) {
  matrix_t matrix_t1, rest;
  int error_targett = 0;
  unsigned int new = 0;
  s21_create_matrix(6, 2, &matrix_t1);
  for (int i = 0; i < matrix_t1.rows; i++) {
    for (int j = 0; j < matrix_t1.columns; j++) {
      matrix_t1.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targett = s21_transpose(&matrix_t1, &rest);
  ck_assert_int_eq(error_targett, 0);
  s21_remove_matrix(&matrix_t1);
  s21_remove_matrix(&rest);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t matrix_t1, rest;
  int error_targett = 0;
  s21_create_matrix(0, 2, &matrix_t1);
  error_targett = s21_transpose(&matrix_t1, &rest);
  ck_assert_int_eq(error_targett, 1);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t matrix_A1mmm, res1mmm;
  int error_target1mmm = 0;
  unsigned int new = 0;
  s21_create_matrix(5, 5, &matrix_A1mmm);
  s21_create_matrix(0, 0, &res1mmm);
  for (int i = 0; i < matrix_A1mmm.rows; i++) {
    for (int j = 0; j < matrix_A1mmm.columns; j++) {
      matrix_A1mmm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target1mmm = s21_calc_complements(&matrix_A1mmm, &res1mmm);
  ck_assert_int_eq(error_target1mmm, 0);
  s21_remove_matrix(&matrix_A1mmm);
  s21_remove_matrix(&res1mmm);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t matrix_A1mmm, res1mmm;
  int error_target1mmm = 0;
  unsigned int new = 0;
  s21_create_matrix(5, 4, &matrix_A1mmm);
  s21_create_matrix(0, 0, &res1mmm);
  for (int i = 0; i < matrix_A1mmm.rows; i++) {
    for (int j = 0; j < matrix_A1mmm.columns; j++) {
      matrix_A1mmm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target1mmm = s21_calc_complements(&matrix_A1mmm, &res1mmm);
  ck_assert_int_eq(error_target1mmm, 1);
  s21_remove_matrix(&matrix_A1mmm);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t matrix_A1mmm, res1mmm;
  int error_target1mmm = 0;
  unsigned int new = 0;
  s21_create_matrix(1, 1, &matrix_A1mmm);
  s21_create_matrix(0, 0, &res1mmm);
  for (int i = 0; i < matrix_A1mmm.rows; i++) {
    for (int j = 0; j < matrix_A1mmm.columns; j++) {
      matrix_A1mmm.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target1mmm = s21_calc_complements(&matrix_A1mmm, &res1mmm);
  ck_assert_int_eq(error_target1mmm, 1);
  s21_remove_matrix(&matrix_A1mmm);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t matrix_A1dd;
  double res1dd;
  int error_target1dd = 0;
  unsigned int new = 0;
  s21_create_matrix(5, 5, &matrix_A1dd);
  for (int i = 0; i < matrix_A1dd.rows; i++) {
    for (int j = 0; j < matrix_A1dd.columns; j++) {
      matrix_A1dd.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target1dd = s21_determinant(&matrix_A1dd, &res1dd);
  ck_assert_int_eq(error_target1dd, 0);
  s21_remove_matrix(&matrix_A1dd);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t matrix_A1dd;
  double res1dd;
  int error_target1dd = 0;
  unsigned int new = 0;
  s21_create_matrix(3, 5, &matrix_A1dd);
  for (int i = 0; i < matrix_A1dd.rows; i++) {
    for (int j = 0; j < matrix_A1dd.columns; j++) {
      matrix_A1dd.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_target1dd = s21_determinant(&matrix_A1dd, &res1dd);
  ck_assert_int_eq(error_target1dd, 1);
  s21_remove_matrix(&matrix_A1dd);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t matrix_Aim1, resim1;
  int error_targetim1 = 0;
  unsigned int new = 0;
  s21_create_matrix(4, 4, &matrix_Aim1);
  s21_create_matrix(0, 0, &resim1);
  for (int i = 0; i < matrix_Aim1.rows; i++) {
    for (int j = 0; j < matrix_Aim1.columns; j++) {
      matrix_Aim1.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetim1 = s21_inverse_matrix(&matrix_Aim1, &resim1);
  ck_assert_int_eq(error_targetim1, 0);
  s21_remove_matrix(&matrix_Aim1);
  s21_remove_matrix(&resim1);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t matrix_Aim1, resim1;
  int error_targetim1 = 0;
  unsigned int new = 0;
  s21_create_matrix(5, 4, &matrix_Aim1);
  s21_create_matrix(0, 0, &resim1);
  for (int i = 0; i < matrix_Aim1.rows; i++) {
    for (int j = 0; j < matrix_Aim1.columns; j++) {
      matrix_Aim1.matrix[i][j] = (rand_r(&new) % 10);
    }
  }
  error_targetim1 = s21_inverse_matrix(&matrix_Aim1, &resim1);
  ck_assert_int_eq(error_targetim1, 1);
  s21_remove_matrix(&matrix_Aim1);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("s21_Debuger");
  SRunner *srunner = srunner_create(suite);
  if (srunner) {
    ;
  }

  // Тестовый кейс s21_create_matrix
  TCase *s21_create_matrix_p_1 = tcase_create("s21_create_matrix");
  suite_add_tcase(suite, s21_create_matrix_p_1);
  tcase_add_test(s21_create_matrix_p_1, s21_create_matrix_1);

  TCase *s21_create_matrix_p_2 = tcase_create("s21_create_matrix");
  suite_add_tcase(suite, s21_create_matrix_p_2);
  tcase_add_test(s21_create_matrix_p_2, s21_create_matrix_2);

  TCase *s21_create_matrix_p_3 = tcase_create("s21_create_matrix");
  suite_add_tcase(suite, s21_create_matrix_p_3);
  tcase_add_test(s21_create_matrix_p_3, s21_create_matrix_3);

  TCase *s21_create_matrix_p_4 = tcase_create("s21_create_matrix");
  suite_add_tcase(suite, s21_create_matrix_p_4);
  tcase_add_test(s21_create_matrix_p_4, s21_create_matrix_4);

  TCase *s21_create_matrix_p_5 = tcase_create("s21_create_matrix");
  suite_add_tcase(suite, s21_create_matrix_p_5);
  tcase_add_test(s21_create_matrix_p_5, s21_create_matrix_5);

  TCase *s21_create_matrix_p_6 = tcase_create("s21_create_matrix");
  suite_add_tcase(suite, s21_create_matrix_p_6);
  tcase_add_test(s21_create_matrix_p_6, s21_create_matrix_6);

  // Тестовый кейс s21_remove_matrix
  TCase *s21_remove_matrix_p_1 = tcase_create("s21_remove_matrix");
  suite_add_tcase(suite, s21_remove_matrix_p_1);
  tcase_add_test(s21_remove_matrix_p_1, s21_remove_matrix_1);

  // Тестовый кейс s21_eq_matrix
  TCase *s21_eq_matrix_p_1 = tcase_create("s21_eq_matrix");
  suite_add_tcase(suite, s21_eq_matrix_p_1);
  tcase_add_test(s21_eq_matrix_p_1, s21_eq_matrix_1);

  TCase *s21_eq_matrix_p_2 = tcase_create("s21_eq_matrix");
  suite_add_tcase(suite, s21_eq_matrix_p_2);
  tcase_add_test(s21_eq_matrix_p_2, s21_eq_matrix_2);

  TCase *s21_eq_matrix_p_3 = tcase_create("s21_eq_matrix");
  suite_add_tcase(suite, s21_eq_matrix_p_3);
  tcase_add_test(s21_eq_matrix_p_3, s21_eq_matrix_3);

  TCase *s21_eq_matrix_p_4 = tcase_create("s21_eq_matrix");
  suite_add_tcase(suite, s21_eq_matrix_p_4);
  tcase_add_test(s21_eq_matrix_p_4, s21_eq_matrix_4);

  TCase *s21_eq_matrix_p_5 = tcase_create("s21_eq_matrix");
  suite_add_tcase(suite, s21_eq_matrix_p_5);
  tcase_add_test(s21_eq_matrix_p_5, s21_eq_matrix_5);

  // Тестовый кейс s21_sum_matrix
  TCase *s21_sum_matrix_p_1 = tcase_create("s21_sum_matrix");
  suite_add_tcase(suite, s21_sum_matrix_p_1);
  tcase_add_test(s21_sum_matrix_p_1, s21_sum_matrix_1);

  TCase *s21_sum_matrix_p_2 = tcase_create("s21_sum_matrix");
  suite_add_tcase(suite, s21_sum_matrix_p_2);
  tcase_add_test(s21_sum_matrix_p_2, s21_sum_matrix_2);

  TCase *s21_sum_matrix_p_3 = tcase_create("s21_sum_matrix");
  suite_add_tcase(suite, s21_sum_matrix_p_3);
  tcase_add_test(s21_sum_matrix_p_3, s21_sum_matrix_3);

  // Тестовый кейс s21_sub_matrix
  TCase *s21_sub_matrix_p_1 = tcase_create("s21_sub_matrix");
  suite_add_tcase(suite, s21_sub_matrix_p_1);
  tcase_add_test(s21_sub_matrix_p_1, s21_sub_matrix_1);

  TCase *s21_sub_matrix_p_2 = tcase_create("s21_sub_matrix");
  suite_add_tcase(suite, s21_sub_matrix_p_2);
  tcase_add_test(s21_sub_matrix_p_2, s21_sub_matrix_2);

  TCase *s21_sub_matrix_p_3 = tcase_create("s21_sub_matrix");
  suite_add_tcase(suite, s21_sub_matrix_p_3);
  tcase_add_test(s21_sub_matrix_p_3, s21_sub_matrix_3);

  // Тестовый кейс s21_mult_number
  TCase *s21_mult_number_p_1 = tcase_create("s21_mult_number");
  suite_add_tcase(suite, s21_mult_number_p_1);
  tcase_add_test(s21_mult_number_p_1, s21_mult_number_1);

  TCase *s21_mult_number_p_2 = tcase_create("s21_mult_number");
  suite_add_tcase(suite, s21_mult_number_p_2);
  tcase_add_test(s21_mult_number_p_2, s21_mult_number_2);

  // Тестовый кейс s21_mult_matrix
  TCase *s21_mult_matrix_p_1 = tcase_create("s21_mult_matrix");
  suite_add_tcase(suite, s21_mult_matrix_p_1);
  tcase_add_test(s21_mult_matrix_p_1, s21_mult_matrix_1);

  TCase *s21_mult_matrix_p_2 = tcase_create("s21_mult_matrix");
  suite_add_tcase(suite, s21_mult_matrix_p_2);
  tcase_add_test(s21_mult_matrix_p_2, s21_mult_matrix_2);

  TCase *s21_mult_matrix_p_3 = tcase_create("s21_mult_matrix");
  suite_add_tcase(suite, s21_mult_matrix_p_3);
  tcase_add_test(s21_mult_matrix_p_3, s21_mult_matrix_3);

  // Тестовый кейс s21_transpose
  TCase *s21_transpose_p_1 = tcase_create("s21_transpose");
  suite_add_tcase(suite, s21_transpose_p_1);
  tcase_add_test(s21_transpose_p_1, s21_transpose_1);

  TCase *s21_transpose_p_2 = tcase_create("s21_transpose");
  suite_add_tcase(suite, s21_transpose_p_2);
  tcase_add_test(s21_transpose_p_2, s21_transpose_2);

  // Тестовый кейс s21_calc_complements
  TCase *s21_calc_complements_p_1 = tcase_create("s21_calc_complements");
  suite_add_tcase(suite, s21_calc_complements_p_1);
  tcase_add_test(s21_calc_complements_p_1, s21_calc_complements_1);

  TCase *s21_calc_complements_p_2 = tcase_create("s21_calc_complements");
  suite_add_tcase(suite, s21_calc_complements_p_2);
  tcase_add_test(s21_calc_complements_p_2, s21_calc_complements_2);

  TCase *s21_calc_complements_p_3 = tcase_create("s21_calc_complements");
  suite_add_tcase(suite, s21_calc_complements_p_3);
  tcase_add_test(s21_calc_complements_p_3, s21_calc_complements_3);

  // Тестовый кейс s21_determinant
  TCase *s21_determinant_p_1 = tcase_create("s21_determinant");
  suite_add_tcase(suite, s21_determinant_p_1);
  tcase_add_test(s21_determinant_p_1, s21_determinant_1);

  TCase *s21_determinant_p_2 = tcase_create("s21_determinant");
  suite_add_tcase(suite, s21_determinant_p_2);
  tcase_add_test(s21_determinant_p_2, s21_determinant_2);

  // Тестовый кейс s21_inverse_matrix
  TCase *s21_inverse_matrix_p_1 = tcase_create("s21_inverse_matrix");
  suite_add_tcase(suite, s21_inverse_matrix_p_1);
  tcase_add_test(s21_inverse_matrix_p_1, s21_inverse_matrix_1);

  TCase *s21_inverse_matrix_p_2 = tcase_create("s21_inverse_matrix");
  suite_add_tcase(suite, s21_inverse_matrix_p_2);
  tcase_add_test(s21_inverse_matrix_p_2, s21_inverse_matrix_2);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

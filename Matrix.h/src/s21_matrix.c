#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error_target = 0;
  if (!(columns > 0) || !(rows > 0)) {
    if (columns == 0 || rows == 0) {
      result->matrix = NULL;
      result->columns = 0;
      result->rows = 0;
    } else {
      error_target = 1;
    }
  } else {
    result->columns = columns;
    result->rows = rows;
    if (!(result->matrix = (double **)calloc(rows, sizeof(double *)))) {
      error_target = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
    }
  }
  return error_target;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error_target = 1;
  if (!(A->columns > 0) || !(B->columns > 0) || !(A->rows > 0) ||
      !(B->rows > 0)) {
    error_target = 1;
  } else if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows && error_target; i++) {
      for (int j = 0; j < A->columns && error_target; j++) {
        if ((long int)(A->matrix[i][j] / 1E-7) !=
            (long int)(B->matrix[i][j] / 1E-7)) {
          error_target = 0;
        }
      }
    }
  } else {
    error_target = 0;
  }
  return error_target;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_target = 0;
  if (!(A->columns == B->columns && A->rows == B->rows)) {
    error_target = 2;
  } else if (!(A->columns > 0) || !(B->columns > 0) || !(A->rows > 0) ||
             !(B->rows > 0)) {
    error_target = 1;
  } else {
    error_target = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && !error_target; i++) {
      for (int j = 0; j < A->columns && !error_target; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error_target;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_target = 0;
  if (!(A->columns == B->columns && A->rows == B->rows)) {
    error_target = 2;
  } else if (!(A->columns > 0) || !(B->columns > 0) || !(A->rows > 0) ||
             !(B->rows > 0)) {
    error_target = 1;
  } else {
    error_target = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && !error_target; i++) {
      for (int j = 0; j < A->columns && !error_target; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error_target;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error_target = 0;
  if (!(A->columns > 0) || !(A->rows > 0)) {
    error_target = 1;
  } else {
    error_target = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && !error_target; i++) {
      for (int j = 0; j < A->columns && !error_target; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error_target;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_target = 0;
  if (A->columns != B->rows) {
    error_target = 2;
  } else if (A->columns < 1 || A->rows < 1 || B->columns < 1 || B->rows < 1) {
    error_target = 1;
  } else {
    error_target = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows && !error_target; i++) {
      for (int j = 0; j < result->columns && !error_target; j++) {
        for (int new = 0; new < A->columns; new ++) {
          result->matrix[i][j] += A->matrix[i][new] * B->matrix[new][j];
        }
      }
    }
  }
  return error_target;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error_target = 0;
  if (!(A->columns > 0) || !(A->rows > 0)) {
    error_target = 1;
  } else {
    error_target = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns && !error_target; i++) {
      for (int j = 0; j < A->rows && !error_target; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return error_target;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error_target = 0;
  if (A->rows != A->columns || A->rows == 1) {
    error_target = 1;
  } else {
    error_target = s21_create_matrix(A->rows, A->columns, result);
    if (!error_target) {
      mino_and_algdop(result, A);
    }
  }
  return error_target;
}

int s21_determinant(matrix_t *A, double *result) {
  int error_target = 0;
  if (A->rows != A->columns) {
    error_target = 1;
  } else {
    matrix_t AA = *A;
    int size_a = A->rows;
    *result = determinant(AA, size_a);
  }
  return error_target;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error_target = 0, size_a = A->rows;
  if (A->rows != A->columns) {
    error_target = 1;
  } else {
    double new;
    new = determinant(*A, size_a);
    if (new != 0) {
      matrix_t AA;
      error_target = s21_calc_complements(A, &AA);
      if (!error_target) {
        error_target = s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < AA.columns && !error_target; i++) {
          for (int j = 0; j < AA.rows && !error_target; j++) {
            result->matrix[i][j] = AA.matrix[j][i];
          }
        }
      }
      s21_remove_matrix(&AA);
    } else {
      error_target = 2;
    }
  }
  return error_target;
}

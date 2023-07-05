#include "s21_matrix.h"

// void print_matrix(matrix_t *new) {
//     if (new->rows > 0 && new->columns > 0) {
//         for (int c = 0; c < new->rows; c++) {
//             for (int r = 0; r < new->columns; r++) {
//                 printf("%.7f ", new->matrix[c][r]);
//             }
//             printf("\n");
//         }
//     }
// }

double determinant(matrix_t A, int size_a) {
  double res = 0;
  if (size_a >= 3) {
    matrix_t temp;
    s21_create_matrix(size_a - 1, size_a - 1, &temp);
    for (int j = 0; j < size_a; j++) {
      int a = 0;
      for (int k = 1; k < size_a; k++) {
        int b = 0;
        for (int s = 0; s < size_a; s++) {
          if (s != j) {
            temp.matrix[a][b] = A.matrix[k][s];
            b++;
          }
        }
        a++;
      }
      res += pow(-1, (double)j + 2) * A.matrix[0][j] *
             determinant(temp, size_a - 1);
    }
    s21_remove_matrix(&temp);
  } else if (size_a == 2) {
    res = opred2x2(&A);
  } else {
    res = A.matrix[0][0];
  }
  return res;
}

int mino_and_algdop(matrix_t *result, matrix_t *A) {
  int error_target = 0;
  for (int i = 0; i < A->rows && !error_target; i++) {
    for (int j = 0; j < A->columns && !error_target; j++) {
      matrix_t new;
      error_target = s21_create_matrix(A->rows - 1, A->rows - 1, &new);
      if (!error_target) {
        cut(i, j, A, &new);
        double m_res = determinant(new, new.rows);
        result->matrix[i][j] = (i + j) % 2 && m_res ? -m_res : m_res;
        s21_remove_matrix(&new);
      }
    }
  }
  return error_target;
}

double opred2x2(matrix_t *A) {
  return (A->matrix[0][0] * A->matrix[1][1] -
          A->matrix[0][1] * A->matrix[1][0]);
}

void cut(int r, int c, matrix_t *A, matrix_t *new) {
  int newr = 0, newc = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != r && j != c) {
        new->matrix[newr][newc] = A->matrix[i][j];
        if (newc == A->columns - 2) {
          newr += 1;
          newc = 0;
        } else {
          newc += 1;
        }
      }
    }
  }
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Matrix_struct - структура для хранения созданой матрицы и данных свзяаных с
   ней

    matrix - Пременая для хранения созданой матрицы
    rows - Длина строк в матрице
    columns - Количество строк в матрице
*/
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Основные функции

// Операция создания матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матрицы
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Умножение матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Вычисление определителя матрицы
int s21_determinant(matrix_t *A, double *result);

// Вычисление обратной матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Выспомогательные функции

// вывод матрицы в терминал
// void print_matrix(matrix_t *new);

// Получение минорной матрицы любого порядка
int mino_and_algdop(matrix_t *result, matrix_t *A);

// Поиск детерменанта матрицы
double determinant(matrix_t A, int size_a);

// детерменант 2х2 матрицы
double opred2x2(matrix_t *A);

// Обрезание матрицы по столбцу и колонке
void cut(int r, int c, matrix_t *A, matrix_t *new);

#include "s21_matrix.h"

//Определитель матрицы
//Определитель матрицы равен сумме произведений
//элементов строки (столбца) на соответствующие алгебраические дополнения.

int s21_determinant(matrix_t *A, double *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      STATUS = EXCEPTION_CAL;
    }
  }
  return STATUS;
}

//вычисляет определитель и записывает его в переменную `result`
double s21_get_determinant(matrix_t *A) {
  double result = 0;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_calc(0, i, A, &tmp);  //вычисляем минор
      if (i % 2) {
        result -= A->matrix[0][i] * s21_get_determinant(&tmp);
      } else {
        result += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return result;
}

//Вычисляются размерности матрицы
//Копируются элементы исходной матрицы во временную, за исключением строки и
//столбца, соответствующих переданным координатам.

void s21_get_calc(int rows, int columns, matrix_t *A, matrix_t *result) {
  int crows = 0;
  int ccolumns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == rows) {
      continue;
    }
    ccolumns = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == columns) {
        continue;
      }
      result->matrix[crows][ccolumns] = A->matrix[i][j];
      ccolumns++;
    }
    crows++;
  }
}

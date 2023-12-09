#include "s21_matrix.h"

//Минор матрицы и матрица алгебраических дополнений
//Минором M(i,j) называется определитель (n-1)-го порядка, полученный
//вычёркиванием из матрицы A i-й строки и j-го столбца.
//знак каждого элемента зависит от расположения столбца и строки
//поэтому используется функция pow для вычисления выражения (-1)^(i+j).

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t calc = {0};
          double determinant = 0;
          s21_create_matrix(A->columns - 1, A->rows - 1, &calc);
          s21_get_calc(i, j, A, &calc);
          s21_determinant(&calc, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&calc);
        }
      }
    } else {
      STATUS = EXCEPTION_CAL;
    }
  }
  return STATUS;
}
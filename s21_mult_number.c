#include "s21_matrix.h"

// Умножение матрицы на число
//Произведением матрицы это равенствщ B = λ × A(i,j)

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    STATUS = EXCEPTION;
  }
  return OK;
}

#include "s21_matrix.h"

//  Умножение двух матриц
// пример как должно быть C(1,1) = A(1,1) × B(1,1) + A(1,2) × B(2,1)

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if (B->rows == A->columns) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      STATUS = EXCEPTION_CAL;
    }
  }
  return STATUS;
}

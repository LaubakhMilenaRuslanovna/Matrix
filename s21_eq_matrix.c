#include "s21_matrix.h"

// Сравнение матриц
//Совпадают их размеры и соответствующие элементы равны

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 1;  // SUCCESS 1
  if (A == NULL || A->matrix == NULL || B == NULL || B->matrix == NULL ||
      A->rows != B->rows || A->columns != B->columns || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    flag = 0;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
          flag = 0;
          break;
        }
      }
    }
  }
  return flag;
}

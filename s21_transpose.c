#include "s21_matrix.h"

//Транспонирование матрицы
//Транспонирование матрицы А заключается в замене строк этой матрицы ее
//столбцами с сохранением их номеров.

int s21_transpose(matrix_t *A, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return STATUS;
}

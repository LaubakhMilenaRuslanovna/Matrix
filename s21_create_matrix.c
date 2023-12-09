#include "s21_matrix.h"

// Создание матри

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = 1;
  result->matrix = NULL;
  if (rows > 0 && columns > 0) {
    result->matrix = (double **)malloc(rows * sizeof(double));
    if (result->matrix != NULL) {
      flag = 0;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
      }
    }
    result->rows = rows;
    result->columns = columns;
  }
  return flag;
}

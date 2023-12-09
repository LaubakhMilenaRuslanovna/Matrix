#include "s21_matrix.h"

//инверсия

int s21_inverse_matrix(matrix_t *A,
                       matrix_t *result) {  // поиск обратной матрицы
  int STATUS = OK;
  if ((A == NULL && A->matrix == NULL) || (A->rows < 0 && A->columns < 0)) {
    STATUS = EXCEPTION;
  } else if (A->rows != A->columns) {
    STATUS = EXCEPTION_CAL;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (fabs(det) > 1e-7) {
      matrix_t tempM1, tempM2;
      s21_calc_complements(A, &tempM1);
      s21_transpose(&tempM1, &tempM2);
      s21_remove_matrix(&tempM1);
      s21_mult_number(&tempM2, 1.0 / det, result);
      s21_remove_matrix(&tempM2);
    } else {
      STATUS = EXCEPTION_CAL;
    }
  }
  return STATUS;
}
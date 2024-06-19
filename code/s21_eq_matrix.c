#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int eq_status = SUCCESS;
  if (A->matrix != NULL && B->matrix != NULL) {
    if (A->rows != B->rows) eq_status = FAILURE;
    if (A->columns != B->columns) eq_status = FAILURE;
    for (int i = 0; i < A->rows && eq_status != FAILURE; i++) {
      for (int j = 0; j < A->columns && eq_status != FAILURE; j++) {
        if (fabs((A->matrix[i][j] - B->matrix[i][j])) > 1e-7)
          eq_status = FAILURE;
      }
    }
  } else {
    eq_status = FAILURE;
  }
  return eq_status;
}
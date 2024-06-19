#include "../common/common.h"
#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  unsigned int status = OK;
  if (result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (!s21_is_valid_matrix(*A) || !s21_is_valid_matrix(*B)) {
    status = ERROR_MATRIX;
  } else if (A->columns != B->rows) {
    status = ERROR_MATRIX;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = s21_sum_for_mult_matrix(A, B, i, j);
      }
    }
  }
  return status;
}

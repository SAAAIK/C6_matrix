#include "../common/common.h"
#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  unsigned int status = OK;
  if (result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (!s21_is_valid_matrix(*A)) {
    status = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return status;
}

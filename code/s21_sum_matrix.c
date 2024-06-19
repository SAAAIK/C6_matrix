#include "../common/common.h"
#include "../s21_matrix.h"
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  unsigned int status = OK;
  if (result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (!s21_is_valid_matrix(*A) || !s21_is_valid_matrix(*B)) {
    status = ERROR_MATRIX;
  } else if (!s21_size_eq_matrix(*A, *B)) {
    status = ERROR_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        // проверять на валидность результат перед записью
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return status;
}
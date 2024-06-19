#include "../common/common.h"
#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  unsigned int status = OK;
  if (result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (!s21_is_valid_matrix(*A) || isinf(number)) {
    status = ERROR_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        // проверять на валидность результат перед записью
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return status;
}
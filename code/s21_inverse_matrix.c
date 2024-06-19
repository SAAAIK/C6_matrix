#include "../common/common.h"
#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  unsigned int status = OK;
  if (!s21_is_valid_matrix(*A)) {
    status = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    status = ERROR_MATRIX;
  } else {
    double det = 0;
    status = s21_determinant(A, &det);
    if (det == 0) {
      status = ERROR_MATRIX;
    } else if (status) {
    } else if (A->rows == 1) {
      s21_create_matrix(A->columns, A->rows, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
    } else {
      matrix_t temp = {0};
      matrix_t transposed = {0};
      s21_calc_complements(A, &temp);
      s21_transpose(&temp, &transposed);
      s21_mult_number(&transposed, 1 / det, result);
      s21_remove_matrix(&temp);
      s21_remove_matrix(&transposed);
    }
  }
  return status;
}

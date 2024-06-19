#include "../common/common.h"
#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;

  if (A == NULL || A->matrix == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    status = ERROR_MATRIX;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else if (A->rows > 2) {
      int sign = 1;
      *result = 0;
      for (int i = 0; i < A->columns && status == OK; i++) {
        matrix_t minor;
        status = s21_create_submatrix(A, 0, i, &minor);
        if (status != OK) {
          break;  // Early return if there's an error
        }
        double minor_det = 0;
        status = s21_determinant(&minor, &minor_det);
        if (!status) {
          *result += sign * A->matrix[0][i] * minor_det;
          sign = -sign;
        }
        s21_remove_matrix(&minor);  // Deallocate minor regardless of status
      }
    }
  }
  return status;
}
#include "../common/common.h"
#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (A->rows == 1 || A->columns == 1) {
    status = ERROR_MATRIX;
  } else {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows && status == OK; i++) {
        int sign = i % 2 == 0 ? 1 : -1;
        for (int j = 0; j < A->columns && status == OK; j++) {
          matrix_t minor;
          s21_create_submatrix(A, i, j, &minor);
          double det = 0;
          status = s21_determinant(&minor, &det);
          if (!status) {
            result->matrix[i][j] = sign * det;
            sign = -sign;
          }
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return status;
}

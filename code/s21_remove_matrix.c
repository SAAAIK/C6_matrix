#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *matrix) {
  if (matrix) {
    for (int i = 0; i < matrix->rows; i++) {
      free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    matrix->matrix = NULL;
    matrix->rows = 0;
    matrix->columns = 0;
  }
}

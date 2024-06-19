#include "../common/common.h"
#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  unsigned int status = OK;
  if (!result || !columns || !rows) {
    status = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      status = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          result->matrix = NULL;
          status = INCORRECT_MATRIX;
          break;
        }
      }
    }
  }
  return status;
}

int s21_create_submatrix(matrix_t *A, int exclude_row, int exclude_col,
                         matrix_t *result) {
  unsigned int status = OK;
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (result->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    int row = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i == exclude_row) continue;
      int col = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j == exclude_col) continue;
        result->matrix[row][col] = A->matrix[i][j];
        col++;
      }
      row++;
    }
  }
  return status;
}
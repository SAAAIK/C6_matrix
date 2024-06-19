#include "common.h"

void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step) {
  if (A != NULL && A->matrix != NULL) {
    double value = start_value;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value;
        value += iteration_step;
      }
    }
  }
}

void s21_print_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        printf("%f\t", A->matrix[i][j]);
      }
      printf("\n");
    }
  }
}

int s21_size_eq_matrix(matrix_t A, matrix_t B) {
  int eq_status = SUCCESS;
  if (A.rows != B.rows || A.columns != B.columns) eq_status = FAILURE;
  return eq_status;
}

int s21_is_valid_matrix(matrix_t A) {
  int eq_status = SUCCESS;
  if (A.matrix != NULL) {
    if (A.rows < 1) eq_status = FAILURE;
    if (A.columns < 1) eq_status = FAILURE;
    for (int i = 0; i < A.rows && eq_status != FAILURE; i++) {
      for (int j = 0; j < A.columns && eq_status != FAILURE; j++) {
        if (isinf(A.matrix[i][j])) eq_status = FAILURE;
      }
    }
  } else {
    eq_status = FAILURE;
  }
  return eq_status;
}

double s21_sum_for_mult_matrix(matrix_t *A, matrix_t *B, int i, int j) {
  int res = 0;
  for (int r = 0; r < B->rows; r++) {
    res += A->matrix[i][r] * B->matrix[r][j];
  }
  return res;
}

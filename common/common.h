#ifndef COMMON_H
#define COMMON_H

#include "../s21_matrix.h"

void s21_print_matrix(matrix_t *A);
void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step);
int s21_size_eq_matrix(matrix_t A, matrix_t B);
int s21_is_valid_matrix(matrix_t A);
double s21_sum_for_mult_matrix(matrix_t *A, matrix_t *B, int i, int j);
int s21_create_submatrix(matrix_t *A, int exclude_row, int exclude_col,
                         matrix_t *result);
#endif
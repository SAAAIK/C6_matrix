#include "tests.h"

int main(void) {
  int failed = 0;
  Suite *s21_matrix_test[] = {s21_create_matrix_suite(),
                              s21_remove_matrix_suite(),
                              s21_eq_matrix_suite(),
                              s21_sum_matrix_suite(),
                              s21_sub_matrix_suite(),
                              s21_mult_number_suite(),
                              s21_mult_suite(),
                              s21_transpose_matrix_suite(),
                              s21_calc_complements_suite(),
                              s21_determinant_suite(),
                              s21_inverse_matrix_suite(),
                              NULL};
  for (int i = 0; s21_matrix_test[i] != NULL; i++) {

    SRunner *sr = srunner_create(s21_matrix_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);
  return failed == 0 ? 0 : 1;
}
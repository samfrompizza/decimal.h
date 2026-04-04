#include <check.h>

#include "test_suites.h"

int main(void) {
  Suite *suites[] = {
      s21_add_test(),
      s21_sub_test(),
      s21_is_less_test(),
      s21_is_less_or_equal_test(),
      s21_is_greater_test(),
      s21_is_greater_or_equal_test(),
      s21_is_equal_test(),
      s21_is_not_equal_test(),
      s21_from_int_to_decimal_test(),
      s21_from_float_to_decimal_test(),
      s21_from_decimal_to_int_test(),
      s21_from_decimal_to_float_test(),
      s21_floor_test(),
      s21_round_test(),
      s21_truncate_test(),
      s21_negate_test(),
  };

  SRunner *runner = srunner_create(suites[0]);
  for (unsigned long i = 1; i < sizeof(suites) / sizeof(suites[0]); ++i) {
    srunner_add_suite(runner, suites[i]);
  }

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed == 0 ? 0 : 1;
}

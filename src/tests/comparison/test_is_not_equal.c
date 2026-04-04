#include <check.h>

#include "../../s21_decimal.h"

START_TEST(not_equal_for_different_numbers) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{11, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(not_equal_for_equivalent_values) {
  s21_decimal a = {{500, 0, 0, 0x00020000}};  // 5.00
  s21_decimal b = {{5, 0, 0, 0}};             // 5
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

Suite *s21_is_not_equal_test(void) {
  Suite *suite = suite_create("s21_is_not_equal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, not_equal_for_different_numbers);
  tcase_add_test(tc, not_equal_for_equivalent_values);
  suite_add_tcase(suite, tc);

  return suite;
}

#include <check.h>

#include "../../s21_decimal.h"

START_TEST(less_or_equal_true_for_less) {
  s21_decimal a = {{99, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(less_or_equal_true_for_equal) {
  s21_decimal a = {{50, 0, 0, 0x00010000}};   // 5.0
  s21_decimal b = {{500, 0, 0, 0x00020000}};  // 5.00
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(less_or_equal_false_for_greater) {
  s21_decimal a = {{101, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

Suite *s21_is_less_or_equal_test(void) {
  Suite *suite = suite_create("s21_is_less_or_equal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, less_or_equal_true_for_less);
  tcase_add_test(tc, less_or_equal_true_for_equal);
  tcase_add_test(tc, less_or_equal_false_for_greater);
  suite_add_tcase(suite, tc);

  return suite;
}

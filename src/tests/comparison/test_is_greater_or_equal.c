#include <check.h>

#include "../../s21_decimal.h"

START_TEST(greater_or_equal_true_for_greater) {
  s21_decimal a = {{1000, 0, 0, 0}};
  s21_decimal b = {{999, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(greater_or_equal_true_for_equal) {
  s21_decimal a = {{1230, 0, 0, 0x00020000}};  // 12.30
  s21_decimal b = {{123, 0, 0, 0x00010000}};   // 12.3
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(greater_or_equal_false_for_less) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST

Suite *s21_is_greater_or_equal_test(void) {
  Suite *suite = suite_create("s21_is_greater_or_equal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, greater_or_equal_true_for_greater);
  tcase_add_test(tc, greater_or_equal_true_for_equal);
  tcase_add_test(tc, greater_or_equal_false_for_less);
  suite_add_tcase(suite, tc);

  return suite;
}

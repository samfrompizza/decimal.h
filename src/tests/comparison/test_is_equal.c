#include <check.h>

#include "../../s21_decimal.h"

START_TEST(equal_same_value_and_scale) {
  s21_decimal a = {{123456, 0, 0, 0x00030000}};
  s21_decimal b = {{123456, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(equal_same_value_different_scale) {
  s21_decimal a = {{10, 0, 0, 0x00010000}};   // 1.0
  s21_decimal b = {{100, 0, 0, 0x00020000}};  // 1.00
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(equal_positive_and_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(equal_different_signs_non_zero) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

Suite *s21_is_equal_test(void) {
  Suite *suite = suite_create("s21_is_equal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, equal_same_value_and_scale);
  tcase_add_test(tc, equal_same_value_different_scale);
  tcase_add_test(tc, equal_positive_and_negative_zero);
  tcase_add_test(tc, equal_different_signs_non_zero);
  suite_add_tcase(suite, tc);

  return suite;
}

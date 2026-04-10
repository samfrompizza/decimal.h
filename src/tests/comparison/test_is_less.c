#include <check.h>

#include "../../s21_decimal.h"

START_TEST(less_positive_numbers) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_negative_and_positive) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_both_negative) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(less_equivalent_scales) {
  s21_decimal a = {{100, 0, 0, 0x00020000}}; // 1.00
  s21_decimal b = {{1, 0, 0, 0}};            // 1
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

Suite *s21_is_less_test(void) {
  Suite *suite = suite_create("s21_is_less");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, less_positive_numbers);
  tcase_add_test(tc, less_negative_and_positive);
  tcase_add_test(tc, less_both_negative);
  tcase_add_test(tc, less_equivalent_scales);
  suite_add_tcase(suite, tc);

  return suite;
}

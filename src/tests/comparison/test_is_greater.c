#include <check.h>

#include "../../s21_decimal.h"

START_TEST(greater_positive_numbers) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(greater_negative_numbers) {
  s21_decimal a = {{2, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(greater_false_for_equal) {
  s21_decimal a = {{1, 0, 0, 0x00010000}};
  s21_decimal b = {{10, 0, 0, 0x00020000}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

Suite *s21_is_greater_test(void) {
  Suite *suite = suite_create("s21_is_greater");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, greater_positive_numbers);
  tcase_add_test(tc, greater_negative_numbers);
  tcase_add_test(tc, greater_false_for_equal);
  suite_add_tcase(suite, tc);

  return suite;
}

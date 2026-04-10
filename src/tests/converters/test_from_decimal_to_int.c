#include <check.h>
#include <limits.h>

#include "../../s21_decimal.h"

START_TEST(decimal_to_int_positive_with_fraction) {
  s21_decimal src = {{1239, 0, 0, 0x00010000}}; // 123.9
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, 123);
}
END_TEST

START_TEST(decimal_to_int_negative_with_fraction) {
  s21_decimal src = {{1239, 0, 0, 0x80010000}}; // -123.9
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, -123);
}
END_TEST

START_TEST(decimal_to_int_int_min) {
  s21_decimal src = {{(int)0x80000000u, 0, 0, 0x80000000}};
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, INT_MIN);
}
END_TEST

START_TEST(decimal_to_int_overflow) {
  s21_decimal src = {{0, 1, 0, 0}};
  int dst = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 1);
}
END_TEST

START_TEST(decimal_to_int_null_dst) {
  s21_decimal src = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, NULL), 1);
}
END_TEST

Suite *s21_from_decimal_to_int_test(void) {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, decimal_to_int_positive_with_fraction);
  tcase_add_test(tc, decimal_to_int_negative_with_fraction);
  tcase_add_test(tc, decimal_to_int_int_min);
  tcase_add_test(tc, decimal_to_int_overflow);
  tcase_add_test(tc, decimal_to_int_null_dst);
  suite_add_tcase(suite, tc);

  return suite;
}

#include <limits.h>

#include <check.h>

#include "../../s21_decimal.h"

START_TEST(from_int_positive) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_int_to_decimal(123456, &dst), 0);
  ck_assert_int_eq(dst.bits[0], 123456);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(from_int_negative) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_int_to_decimal(-123, &dst), 0);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq((dst.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(from_int_min_value) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_int_to_decimal(INT_MIN, &dst), 0);
  ck_assert_int_eq((unsigned int)dst.bits[0], 2147483648u);
  ck_assert_int_eq((dst.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(from_int_null_dst) {
  ck_assert_int_eq(s21_from_int_to_decimal(1, NULL), 1);
}
END_TEST

Suite *s21_from_int_to_decimal_test(void) {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, from_int_positive);
  tcase_add_test(tc, from_int_negative);
  tcase_add_test(tc, from_int_min_value);
  tcase_add_test(tc, from_int_null_dst);
  suite_add_tcase(suite, tc);

  return suite;
}

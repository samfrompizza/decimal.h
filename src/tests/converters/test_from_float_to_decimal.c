#include <check.h>
#include <float.h>

#include "../../s21_decimal.h"

START_TEST(float_to_decimal_simple) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(123.5f, &dst), 0);
  ck_assert_int_eq(s21_from_decimal_to_int(dst, &(int){0}), 0);
}
END_TEST

START_TEST(float_to_decimal_small_value_error) {
  s21_decimal dst = {{1, 2, 3, 4}};
  ck_assert_int_eq(s21_from_float_to_decimal(1e-29f, &dst), 1);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_nan_or_inf_error) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(1.0f / 0.0f, &dst), 1);
  ck_assert_int_eq(s21_from_float_to_decimal(0.0f / 0.0f, &dst), 1);
}
END_TEST

START_TEST(float_to_decimal_zero) {
  s21_decimal dst = {{1, 1, 1, 1}};
  ck_assert_int_eq(s21_from_float_to_decimal(0.0f, &dst), 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_null_dst) {
  ck_assert_int_eq(s21_from_float_to_decimal(1.0f, NULL), 1);
}
END_TEST

Suite *s21_from_float_to_decimal_test(void) {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, float_to_decimal_simple);
  tcase_add_test(tc, float_to_decimal_small_value_error);
  tcase_add_test(tc, float_to_decimal_nan_or_inf_error);
  tcase_add_test(tc, float_to_decimal_zero);
  tcase_add_test(tc, float_to_decimal_null_dst);
  suite_add_tcase(suite, tc);

  return suite;
}

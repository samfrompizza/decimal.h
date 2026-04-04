#include <check.h>
#include <math.h>

#include "../../s21_decimal.h"

START_TEST(decimal_to_float_simple) {
  s21_decimal src = {{12345, 0, 0, 0x00020000}};  // 123.45
  float dst = 0.0f;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq_tol(dst, 123.45f, 1e-4f);
}
END_TEST

START_TEST(decimal_to_float_negative) {
  s21_decimal src = {{10, 0, 0, 0x80010000}};  // -1.0
  float dst = 0.0f;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq_tol(dst, -1.0f, 1e-6f);
}
END_TEST

START_TEST(decimal_to_float_null_dst) {
  s21_decimal src = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(src, NULL), 1);
}
END_TEST

Suite *s21_from_decimal_to_float_test(void) {
  Suite *suite = suite_create("s21_from_decimal_to_float");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, decimal_to_float_simple);
  tcase_add_test(tc, decimal_to_float_negative);
  tcase_add_test(tc, decimal_to_float_null_dst);
  suite_add_tcase(suite, tc);

  return suite;
}

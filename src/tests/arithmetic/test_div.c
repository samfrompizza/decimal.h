#include <check.h>
#include <math.h>

#include "../../s21_decimal.h"

START_TEST(div_simple_integer) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 25);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_fractional_result) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{4, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 25);
  ck_assert_int_eq((res.bits[3] & 0x00FF0000), 0x00010000);  // 2.5
}
END_TEST

START_TEST(div_different_scales) {
  s21_decimal a = {{15, 0, 0, 0x00010000}};  // 1.5
  s21_decimal b = {{5, 0, 0, 0x00010000}};   // 0.5
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 3);
  ck_assert_int_eq((res.bits[3] & 0x00FF0000), 0);
}
END_TEST

START_TEST(div_negative_result) {
  s21_decimal a = {{20, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 4);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(div_zero_dividend) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal b = {{7, 0, 0, 0}};
  s21_decimal res = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_div(zero, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, (s21_decimal){{0, 0, 0, 0}}), 1);
}
END_TEST

START_TEST(div_by_zero_returns_error) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_div(a, zero, &res), 3);
}
END_TEST

START_TEST(div_recurring_fraction_precision) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal res = {{0}};
  float f = 0.0f;

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(s21_from_decimal_to_float(res, &f), 0);
  ck_assert_float_lt(fabsf(f - (1.0f / 3.0f)), 1e-6f);
}
END_TEST

START_TEST(div_overflow_positive) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal tiny = {{1, 0, 0, 0x001C0000}};  // 1e-28
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_div(max, tiny, &res), 1);
}
END_TEST

START_TEST(div_null_result_returns_error) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, NULL), 1);
}
END_TEST

Suite *s21_div_test(void) {
  Suite *suite = suite_create("s21_div");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, div_simple_integer);
  tcase_add_test(tc, div_fractional_result);
  tcase_add_test(tc, div_different_scales);
  tcase_add_test(tc, div_negative_result);
  tcase_add_test(tc, div_zero_dividend);
  tcase_add_test(tc, div_by_zero_returns_error);
  tcase_add_test(tc, div_recurring_fraction_precision);
  tcase_add_test(tc, div_overflow_positive);
  tcase_add_test(tc, div_null_result_returns_error);
  suite_add_tcase(suite, tc);

  return suite;
}

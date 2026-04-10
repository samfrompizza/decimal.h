#include <check.h>

#include "../../s21_decimal.h"

START_TEST(mul_simple_positive) {
  s21_decimal a = {{12, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 36);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_with_scale) {
  s21_decimal a = {{123, 0, 0, 0x00010000}};  // 12.3
  s21_decimal b = {{4, 0, 0, 0}};             // 4
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 492);  // 49.2
  ck_assert_int_eq((res.bits[3] & 0x00FF0000), 0x00010000);
}
END_TEST

START_TEST(mul_negative_by_positive) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{6, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 42);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(mul_by_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, (s21_decimal){{0, 0, 0, 0}}), 1);
}
END_TEST

START_TEST(mul_overflow_positive) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal two = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(max, two, &res), 1);
}
END_TEST

START_TEST(mul_overflow_negative) {
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal two = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(min, two, &res), 2);
}
END_TEST

START_TEST(mul_max_by_tenth_no_overflow) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal tenth = {{1, 0, 0, 0x00010000}};  // 0.1
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_mul(max, tenth, &res), 0);
  ck_assert_int_eq((res.bits[3] & 0x00FF0000), 0x00010000);
}
END_TEST

START_TEST(mul_null_result_returns_error) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, NULL), 1);
}
END_TEST

Suite *s21_mul_test(void) {
  Suite *suite = suite_create("s21_mul");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mul_simple_positive);
  tcase_add_test(tc, mul_with_scale);
  tcase_add_test(tc, mul_negative_by_positive);
  tcase_add_test(tc, mul_by_zero);
  tcase_add_test(tc, mul_overflow_positive);
  tcase_add_test(tc, mul_overflow_negative);
  tcase_add_test(tc, mul_max_by_tenth_no_overflow);
  tcase_add_test(tc, mul_null_result_returns_error);
  suite_add_tcase(suite, tc);

  return suite;
}

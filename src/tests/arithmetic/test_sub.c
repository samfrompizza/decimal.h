#include <check.h>

#include "../../s21_decimal.h"

START_TEST(sub_simple_positive) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{40, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 60);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_negative_result) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{8, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 3);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(sub_different_scales) {
  s21_decimal a = {{100, 0, 0, 0x00010000}}; // 10.0
  s21_decimal b = {{25, 0, 0, 0x00010000}};  // 2.5
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 75);
  ck_assert_int_eq(res.bits[3], 0x00010000);
}
END_TEST

START_TEST(sub_overflow_negative) {
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_sub(min, one, &res), 2);
}
END_TEST

START_TEST(sub_null_result_returns_error) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(a, b, NULL), 1);
}
END_TEST

Suite *s21_sub_test(void) {
  Suite *suite = suite_create("s21_sub");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sub_simple_positive);
  tcase_add_test(tc, sub_negative_result);
  tcase_add_test(tc, sub_different_scales);
  tcase_add_test(tc, sub_overflow_negative);
  tcase_add_test(tc, sub_null_result_returns_error);
  suite_add_tcase(suite, tc);

  return suite;
}

#include <check.h>

#include "../../s21_decimal.h"

START_TEST(add_simple_positive) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{25, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 35);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_different_scales) {
  s21_decimal a = {{15, 0, 0, 0x00010000}};   // 1.5
  s21_decimal b = {{225, 0, 0, 0x00020000}};  // 2.25
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(res.bits[0], 375);
  ck_assert_int_eq(res.bits[3], 0x00020000);
}
END_TEST

START_TEST(add_opposite_signs_cancel) {
  s21_decimal a = {{12345, 0, 0, 0x80000000}};
  s21_decimal b = {{12345, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, (s21_decimal){{0, 0, 0, 0}}), 1);
}
END_TEST

START_TEST(add_overflow_positive) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal res = {{0}};

  ck_assert_int_eq(s21_add(max, one, &res), 1);
}
END_TEST

START_TEST(add_null_result_returns_error) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, NULL), 1);
}
END_TEST

Suite *s21_add_test(void) {
  Suite *suite = suite_create("s21_add");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, add_simple_positive);
  tcase_add_test(tc, add_different_scales);
  tcase_add_test(tc, add_opposite_signs_cancel);
  tcase_add_test(tc, add_overflow_positive);
  tcase_add_test(tc, add_null_result_returns_error);
  suite_add_tcase(suite, tc);

  return suite;
}

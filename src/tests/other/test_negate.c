#include <check.h>

#include "../../s21_decimal.h"

START_TEST(negate_positive) {
  s21_decimal src = {{9, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_negate(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 9);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(negate_negative) {
  s21_decimal src = {{9, 0, 0, 0x80000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_negate(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 9);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 0);
}
END_TEST

START_TEST(negate_negative_zero) {
  s21_decimal src = {{0, 0, 0, 0x80000000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_negate(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 0);
}
END_TEST

START_TEST(negate_null_result) {
  s21_decimal src = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_negate(src, NULL), 1);
}
END_TEST

Suite *s21_negate_test(void) {
  Suite *suite = suite_create("s21_negate");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, negate_positive);
  tcase_add_test(tc, negate_negative);
  tcase_add_test(tc, negate_negative_zero);
  tcase_add_test(tc, negate_null_result);
  suite_add_tcase(suite, tc);

  return suite;
}

#include <check.h>

#include "../../s21_decimal.h"

START_TEST(truncate_positive_fraction) {
  s21_decimal src = {{299, 0, 0, 0x00020000}}; // 2.99
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_truncate(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(truncate_negative_fraction) {
  s21_decimal src = {{299, 0, 0, 0x80020000}}; // -2.99
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_truncate(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(truncate_zero_value) {
  s21_decimal src = {{0, 0, 0, 0x80050000}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_truncate(src, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, (s21_decimal){{0, 0, 0, 0}}), 1);
}
END_TEST

START_TEST(truncate_null_result) {
  s21_decimal src = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(src, NULL), 1);
}
END_TEST

Suite *s21_truncate_test(void) {
  Suite *suite = suite_create("s21_truncate");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, truncate_positive_fraction);
  tcase_add_test(tc, truncate_negative_fraction);
  tcase_add_test(tc, truncate_zero_value);
  tcase_add_test(tc, truncate_null_result);
  suite_add_tcase(suite, tc);

  return suite;
}

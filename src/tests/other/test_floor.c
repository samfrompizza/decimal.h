#include <check.h>

#include "../../s21_decimal.h"

START_TEST(floor_positive_fraction) {
  s21_decimal src = {{29, 0, 0, 0x00010000}}; // 2.9
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_floor(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(floor_negative_fraction) {
  s21_decimal src = {{21, 0, 0, 0x80010000}}; // -2.1
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_floor(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 3);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(floor_integer_keeps_value) {
  s21_decimal src = {{42, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_floor(src, &res), 0);
  ck_assert_int_eq(s21_is_equal(src, res), 1);
}
END_TEST

START_TEST(floor_null_result) {
  s21_decimal src = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_floor(src, NULL), 1);
}
END_TEST

Suite *s21_floor_test(void) {
  Suite *suite = suite_create("s21_floor");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, floor_positive_fraction);
  tcase_add_test(tc, floor_negative_fraction);
  tcase_add_test(tc, floor_integer_keeps_value);
  tcase_add_test(tc, floor_null_result);
  suite_add_tcase(suite, tc);

  return suite;
}

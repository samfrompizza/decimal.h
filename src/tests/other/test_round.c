#include <check.h>

#include "../../s21_decimal.h"

START_TEST(round_positive_down) {
  s21_decimal src = {{24, 0, 0, 0x00010000}}; // 2.4
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_round(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 2);
}
END_TEST

START_TEST(round_positive_up) {
  s21_decimal src = {{25, 0, 0, 0x00010000}}; // 2.5
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_round(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 3);
}
END_TEST

START_TEST(round_negative_half) {
  s21_decimal src = {{25, 0, 0, 0x80010000}}; // -2.5
  s21_decimal res = {{0}};
  ck_assert_int_eq(s21_round(src, &res), 0);
  ck_assert_int_eq(res.bits[0], 3);
  ck_assert_int_eq((res.bits[3] & 0x80000000) != 0, 1);
}
END_TEST

START_TEST(round_null_result) {
  s21_decimal src = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_round(src, NULL), 1);
}
END_TEST

Suite *s21_round_test(void) {
  Suite *suite = suite_create("s21_round");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, round_positive_down);
  tcase_add_test(tc, round_positive_up);
  tcase_add_test(tc, round_negative_half);
  tcase_add_test(tc, round_null_result);
  suite_add_tcase(suite, tc);

  return suite;
}

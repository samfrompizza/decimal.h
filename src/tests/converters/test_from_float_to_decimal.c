#include <check.h>
#include <float.h>
#include <stdint.h>

#include "../../helpers/s21_helpers.h"
#include "../../s21_decimal.h"

static int dec_scale(s21_decimal d) {
  return (int)(((uint32_t)d.bits[3] >> 16) & 0xFFu);
}

static int dec_sign(s21_decimal d) {
  return (int)(((uint32_t)d.bits[3] >> 31) & 1u);
}

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

START_TEST(float_to_decimal_large_value_error) {
  s21_decimal dst = {{1, 2, 3, 4}};
  ck_assert_int_eq(s21_from_float_to_decimal(1e29f, &dst), 1);
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

START_TEST(float_to_decimal_negative_and_trim_zeros) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(-123.45f, &dst), 0);
  ck_assert_int_eq(dec_sign(dst), 1);
  ck_assert_int_eq(dec_scale(dst), 2);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
}
END_TEST

START_TEST(float_to_decimal_normalize_up_and_mul10) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(12345678.0f, &dst), 0);
  ck_assert_int_eq(dec_sign(dst), 0);
  ck_assert_int_eq(dec_scale(dst), 0);
  ck_assert_int_eq(dst.bits[0], 12345680);
}
END_TEST

START_TEST(float_to_decimal_normalize_down_and_round_up) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(0.12345678f, &dst), 0);
  ck_assert_int_eq(dec_sign(dst), 0);
  ck_assert_int_eq(dec_scale(dst), 7);
  ck_assert_int_eq(dst.bits[0], 1234568);
}
END_TEST

START_TEST(float_to_decimal_round_down_no_increment) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(0.12345005f, &dst), 0);
  ck_assert_int_eq(dec_scale(dst), 5);
  ck_assert_int_eq(dst.bits[0], 12345);
}
END_TEST

START_TEST(float_to_decimal_round_tie_increment) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(0.10000005f, &dst), 0);
  ck_assert_int_eq(dec_scale(dst), 7);
  ck_assert_int_eq(dst.bits[0], 1000001);
}
END_TEST

START_TEST(float_to_decimal_small_scale_reduction) {
  s21_decimal dst = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(1.2345678e-23f, &dst), 0);
  ck_assert_int_eq(dec_scale(dst), 28);
  ck_assert_int_eq(dst.bits[0], 123457);
}
END_TEST

Suite *s21_from_float_to_decimal_test(void) {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, float_to_decimal_simple);
  tcase_add_test(tc, float_to_decimal_small_value_error);
  tcase_add_test(tc, float_to_decimal_large_value_error);
  tcase_add_test(tc, float_to_decimal_nan_or_inf_error);
  tcase_add_test(tc, float_to_decimal_zero);
  tcase_add_test(tc, float_to_decimal_null_dst);

  tcase_add_test(tc, float_to_decimal_negative_and_trim_zeros);
  tcase_add_test(tc, float_to_decimal_normalize_up_and_mul10);
  tcase_add_test(tc, float_to_decimal_normalize_down_and_round_up);
  tcase_add_test(tc, float_to_decimal_round_down_no_increment);
  tcase_add_test(tc, float_to_decimal_round_tie_increment);
  tcase_add_test(tc, float_to_decimal_small_scale_reduction);

  suite_add_tcase(suite, tc);
  return suite;
}
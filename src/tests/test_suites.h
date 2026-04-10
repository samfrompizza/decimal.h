#ifndef TEST_SUITES_H
#define TEST_SUITES_H

#include <check.h>

Suite *s21_add_test(void);
Suite *s21_sub_test(void);
Suite *s21_mul_test(void);
Suite *s21_div_test(void);

Suite *s21_is_less_test(void);
Suite *s21_is_less_or_equal_test(void);
Suite *s21_is_greater_test(void);
Suite *s21_is_greater_or_equal_test(void);
Suite *s21_is_equal_test(void);
Suite *s21_is_not_equal_test(void);

Suite *s21_from_int_to_decimal_test(void);
Suite *s21_from_float_to_decimal_test(void);
Suite *s21_from_decimal_to_int_test(void);
Suite *s21_from_decimal_to_float_test(void);

Suite *s21_floor_test(void);
Suite *s21_round_test(void);
Suite *s21_truncate_test(void);
Suite *s21_negate_test(void);

#endif

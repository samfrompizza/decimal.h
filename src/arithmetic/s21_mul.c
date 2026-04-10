#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result)
    return 0;

  for (int i = 0; i < 4; i++)
    result->bits[i] = 0;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int sign_res = (sign_1 != sign_2);
  big_decimal big_value_1, big_value_2, big_res;
  for (int i = 0; i < 7; i++)
    big_res.bits[i] = 0;
  s21_expand(value_1, &big_value_1);
  s21_expand(value_2, &big_value_2);
  s21_mul_mantissa(big_value_1, big_value_2, &big_res);
  big_res.sign = sign_res;
  big_res.scale = big_value_1.scale + big_value_2.scale;
  return s21_normalize(big_res, result);
}
#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result)
    return 0;

  int res = 0;
  for (int i = 0; i < 4; i++)
    result->bits[i] = 0;
  s21_decimal negate_value_2;
  if (s21_negate(value_2, &negate_value_2) == 0) {
    res = s21_add(value_1, negate_value_2, result);
  }
  return res;
}
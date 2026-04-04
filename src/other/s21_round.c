#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int fl_finish = 0;
  if (!result)
    fl_finish = 1;
  else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }
    int value_scale = s21_get_scale(value);
    if (value_scale == 0)
      *result = value;
    else {
      int rem = 0;
      big_decimal big_value;
      s21_expand(value, &big_value);
      while (big_value.scale > 0) {
        rem = s21_div_by_10(&big_value);
        big_value.scale--;
      }
      if (rem >= 5)
        s21_add_1(&big_value);

      result->bits[0] = (uint32_t)big_value.bits[0];
      result->bits[1] = (uint32_t)big_value.bits[1];
      result->bits[2] = (uint32_t)big_value.bits[2];
      if (big_value.sign) {
        s21_set_sign(result);
      }
    }
  }
  return fl_finish;
}